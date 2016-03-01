/*
 * SSerial.h
 *
 * Created: 20.02.2016 14:40:48
 *  Author: Benny Stark (Benny_Stark @ live.de)
 * loosely based on AVR304
 */ 


#ifndef SSERIAL_H_
#define SSERIAL_H_

#include "board.h"

#define SSERIAL_ID_STATE 0x00
#define SSERIAL_TX_STATE 0x01
#define SSERIAL_RX_STATE 0x02

#define SSERIAL_PCINT_ENABLE()	(SSERIAL_PCMSK |= (1<<SSERIAL_PCINT))
#define SSERIAL_PCINT_DISABLE() (SSERIAL_PCMSK &= ~(1<<SSERIAL_PCINT))
#define SSERIAL_PCINT_CLEAR_IF()		(PCIFR |= (1<<SSERIAL_PCINT_IF)) // 1 zum löschen schreiben

void SSerial_init(void);
void SSerial_StackingTask(void);
void SSerial_StackingFunc(char*);

#endif /* SSERIAL_H_ */