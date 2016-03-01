/*
 * SSerial.h
 *
 * Created: 20.02.2016 14:40:48
 *  Author: Benny Stark (Benny_Stark @ live.de)
 * loosely based on AVR304
 */ 


#ifndef SSERIAL_H_
#define SSERIAL_H_

#include <avr/io.h>

#define SSERIAL_ID_STATE 0x00
#define SSERIAL_TX_STATE 0x01
#define SSERIAL_RX_STATE 0x02

#define SSERIAL_DDR		DDRC
#define SSERIAL_PORT	PORTC
#define SSERIAL_PIN		PINC
#define SSERIAL_RX_PIN	PINC0
#define SSERIAL_TX_PIN  PINC1

#define SSERIAL_PCIE    PCIE1
#define SSERIAL_PCMSK	PCMSK1
#define SSERIAL_PCINT	PCINT8
#define SSERIAL_PCINT_VECT PCINT1_vect

#define SSERIAL_PCINT_ENABLE()	(SSERIAL_PCMSK |= (1<<SSERIAL_PCINT))
#define SSERIAL_PCINT_DISABLE() (SSERIAL_PCMSK &= ~(1<<SSERIAL_PCINT))
#define SSERIAL_PCINT_CLEAR_IF()		(PCIFR |= (1<<PCIF1)) // 1 zum löschen schreiben
/*
	CS22 CS21 CS20 Description
	0 0 0 No clock source (Timer/Counter stopped).
	0 0 1 clkT2S/(No prescaling)
	0 1 0 clkT2S/8 (From prescaler)
	0 1 1 clkT2S/32 (From prescaler)
	1 0 0 clkT2S/64 (From prescaler)
	*/
#define SSERIAL_TIMER_DISABLE() (TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20)))
#define SSERIAL_TIMER_ENABLE()	(TCCR2B |=  (1<<CS21) ) //Prescale 8 1us
#define SSERIAL_TIMER_1BIT()			(OCR2A = 104) // Timerlänge Bits (8000000 / 8 * 1 / 38400 = 26,04) (HZ/Prescaler*1/Baud) 104=9600baud / 38400 zu schnell...
#define SSERIAL_TIMER_15BIT()			(OCR2A = 156) //evtl nen bisschen weniger wegen ISR???
#define SSERIAL_TIMER_RESET()			(TCNT2 = 0)

void SSerial_init(void);
void SSerial_StackingTask(void);
void SSerial_StackingFunc(char*);

#endif /* SSERIAL_H_ */