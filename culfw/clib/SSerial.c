/*
 * SSerial.c
 *
 * Created: 20.02.2016 14:31:59
 *  Author: Benny Stark (Benny_Stark @ live.de)
 * loosely based on AVR304
 *
 * Error Behandlung einbauen/ausbauen, wenn state mal nicht idle war cmd verwerfen /markieren
 */ 

#include "SSerial.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include "board.h"
#include "stringfunc.h"
#include "display.h"
#include "clock.h"

volatile char SSerial_State;	// Status ID/TX/RX
volatile char SSerial_Bit;	// Bit Counter

volatile char SSerial_RX;	//RX Data
char SSerial_TX;			// TX Data

//Stacking 
char SSerial_StackingCmd[256];
volatile uint8_t SSerial_StackingPos;
volatile uint8_t SSerial_StackingCmdEOL;


void SSerial_init(void) {
	//TX Init PC1
	SSERIAL_DDR |= (1<<SSERIAL_TX_PIN); // 1= Output
	SSERIAL_PORT |= (1<<SSERIAL_TX_PIN); // Auf High
	
	//RX Init PC0
	SSERIAL_DDR &= ~(1<<SSERIAL_RX_PIN); // 0 = Eingang
	//SSERIAL_PORT |= (1<<SSERIAL_RX_PIN); //Pullup an
	
	//Timer Init
	SSERIAL_TIMER_DISABLE();
	//TCCR2A = 0x00; //Clear Timer mode
	TCCR2A |= (1<<WGM21); //Enable CTC-Mode, no Ports connected, OCR2A 
		
	//Interupt Init
	TIMSK2 |= (1<<OCIE2A); //Interupt Timer 2
	
	PCICR |= (1<<SSERIAL_PCIE); //Enable PINchange
	SSERIAL_PCINT_ENABLE(); //PINChange Interrupt auf PCINT - durch Pullup fällt er auf Null und wird dann disabled in der ISR
	sei();
	
	// Alles Vars leeren
	SSerial_RX = 0x00;
	SSerial_TX = 0x00;
	SSerial_Bit = 0x00;
	SSerial_StackingPos = 0;	
	SSerial_StackingCmdEOL = 0;
	SSerial_StackingCmd[SSerial_StackingPos] = 0;
}

ISR(TIMER2_COMPA_vect) {
	switch (SSerial_State){
		case SSERIAL_RX_STATE:
			if (SSerial_Bit < 8) { //Noch Daten
				SSERIAL_TIMER_1BIT();
				if ((SSERIAL_PIN & (1<<SSERIAL_RX_PIN)) == 0){ //Wenn nicht 0
					SSerial_RX &= ~(1<<SSerial_Bit);
				} else {
					SSerial_RX |= (1<<SSerial_Bit);
				}
				//nächstes BIt
				SSerial_Bit++;
			}else { //9Bit StopBit (Startbit ist im PCint empfangen, wird nicht mitgezählt)
				SSERIAL_TIMER_DISABLE();
				//SSerial_Bit = 0;
				SSerial_State = SSERIAL_ID_STATE;
				//Daten in CMD schreiben
				if (SSerial_RX == 10 ) { // CMD ende / CR
					SSerial_StackingCmd[SSerial_StackingPos]=0; //0Byte
					SSerial_StackingCmdEOL = 1; // Ein Cmd im Buffer
				} else if (SSerial_RX != 13) { //Ansonsten / ausser bei LE
					SSerial_StackingCmd[SSerial_StackingPos] = SSerial_RX;
					SSerial_StackingPos++;
				}

				SSERIAL_PCINT_ENABLE(); // Interrupt wieder enable - damit wieder empfangen werden kann
			}
			break;
		
		case SSERIAL_TX_STATE:
			if (SSerial_Bit < 8) { // Bit übertragen
				if (SSerial_TX & 0x01)
					SSERIAL_PORT  |= (1<<SSERIAL_TX_PIN);
				else 
					SSERIAL_PORT  &= ~(1<<SSERIAL_TX_PIN);
				SSerial_TX = SSerial_TX>>1; // Einen nach rechts
				SSerial_Bit++;
			} else if (SSerial_Bit == 8) { // Stop 9 Bit
				SSERIAL_PORT |= (1<<SSERIAL_TX_PIN); //StopBit ist immer HIGH
				SSerial_Bit++;
			} else if (SSerial_Bit > 8) {// NAch dem Stopbit
				//Timer aus und Idle Stat
				SSERIAL_TIMER_DISABLE();
				SSerial_Bit = 0;
				SSerial_State = SSERIAL_ID_STATE;
			}
			break;
			
		default: // Sollte nie eintreten
			SSerial_State = SSERIAL_ID_STATE;
	}	
}

ISR(SSERIAL_PCINT_VECT) {
	//Keine Prüfung da nur PCINT8 Maskiert ist
	if (SSerial_State == SSERIAL_ID_STATE &&  !SSerial_StackingCmdEOL) {//prüfen ob IDLE und ob noch kein vollständiges cmd da ist
		SSERIAL_PCINT_DISABLE();
		SSERIAL_PCINT_CLEAR_IF();
		SSERIAL_TIMER_DISABLE();
		SSERIAL_TIMER_15BIT();
		SSERIAL_TIMER_RESET();
		
		SSerial_Bit=0;
		SSerial_State = SSERIAL_RX_STATE;
		SSerial_RX = 0x00;
		TIFR2 |= (1 << OCF2A);
		SSERIAL_TIMER_ENABLE();	
	}
}

void SSerial_SendCharBlocking(char c) {
	while(SSerial_State != SSERIAL_ID_STATE);
	SSerial_State = SSERIAL_TX_STATE;
	SSerial_Bit = 0;
	SSerial_TX  = c;
	SSERIAL_TIMER_DISABLE();
	SSERIAL_TIMER_1BIT();
	SSERIAL_TIMER_RESET();
	SSERIAL_PORT &= ~(1<<SSERIAL_TX_PIN); // Startbit
	SSERIAL_TIMER_ENABLE();
}

//Downlink Message received on HW UART
void SSerial_StackingFunc(char* in) {
	uint8_t i = 1; // 1 da das Sternchen weg soll
	while (in[i])  { // bis zum 0Byte
		SSerial_SendCharBlocking(in[i]);
		i++;
	}
	SSerial_SendCharBlocking(13);
	SSerial_SendCharBlocking(10);
}

//Uplink a Message Received by us
void SSerial_StackingTask(void) { 
	if (SSerial_StackingCmdEOL) {
		// Send Data
		DC( '*' );
		DS( SSerial_StackingCmd );
		DNL();		
		// Reset CMD
		SSerial_StackingPos = 0;
		SSerial_StackingCmd[SSerial_StackingPos] = 0;
		SSerial_StackingCmdEOL = 0;
	}
		
}
