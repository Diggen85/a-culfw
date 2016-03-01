#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>

/* if you have an Arduino with only 8MHz disable the next line */
//#define HAS_16MHZ_CLOCK

/* Enables Software Serial Stacking and sets Baudrate to 9600*/
#define HAS_SSERIAL



/* if you are using a CC1101 module for 868MHz disable the next line */
#if defined (nanoCUL433)
#define HAS_CC1100_433
#endif

#define SPI_PORT		PORTB
#define SPI_DDR			DDRB
#define SPI_SS			2
#define SPI_MISO		4
#define SPI_MOSI		3
/* die aufgelötete gelbe LED ist an PB5/SCLK angeschlossen! */
#define SPI_SCLK		5

#define CC1100_CS_DDR		SPI_DDR
#define CC1100_CS_PORT          SPI_PORT
#define CC1100_CS_PIN		SPI_SS


/* CC1101 GDO0 Tx / Temperature Sensor */
#if 0
#define CC1100_OUT_DDR		DDRC
#define CC1100_OUT_PORT         PORTC
#define CC1100_OUT_PIN          PC0
#define CC1100_OUT_IN           PINC
#define CCTEMP_MUX              CC1100_OUT_PIN
#else
#define CC1100_OUT_DDR		DDRD
#define CC1100_OUT_PORT         PORTD
#define CC1100_OUT_PIN          PD3
#define CC1100_OUT_IN           PIND
#define CCTEMP_MUX              CC1100_OUT_PIN
#endif

/* CC1101 GDO2 Rx Interrupt */
#define CC1100_IN_DDR		DDRD
#define CC1100_IN_PORT          PIND
#define CC1100_IN_PIN           PD2
#define CC1100_IN_IN            PIND

#define CC1100_INT		INT0
#define CC1100_INTVECT          INT0_vect
#define CC1100_ISC		ISC00
#define CC1100_EICR             EICRA

/* externe LED */
#define LED_DDR                 DDRB
#define LED_PORT                PORTB
#define LED_PIN                 1

#define BOARD_ID_STR            "nanoCUL868"
#define BOARD_ID_STR433         "nanoCUL433"

/* define this device as a 433 MHz one */
/* this isn't done like a CUL by reading a port pin but instead a fixed value of 0 for mark433_pin is used */ 
#define MULTI_FREQ_DEVICE
#define MARK433_PIN 			mark433_pin
#define MARK433_BIT             0
extern const uint8_t mark433_pin;

#define HAS_UART
#if defined HAS_SSERIAL
	#define UART_BAUD_RATE          9600
#else
	#define UART_BAUD_RATE          38400
#endif

#define TTY_BUFSIZE             128

#define RCV_BUCKETS            2      //                 RAM: 25b * bucket
#define FULL_CC1100_PA                // PROGMEM:  108b
#define HAS_RAWSEND                   //
#define HAS_FASTRF                    // PROGMEM:  468b  RAM:  1b
#define HAS_ASKSIN


#define HAS_CC1101_RX_PLL_LOCK_CHECK_TASK_WAIT
#define HAS_CC1101_PLL_LOCK_CHECK_MSG
#define HAS_CC1101_PLL_LOCK_CHECK_MSG_SW

#if defined HAS_SSERIAL
	/*SSerial RX/TX Port/Pin */
	#define SSERIAL_DDR		DDRC
	#define SSERIAL_PORT	PORTC
	#define SSERIAL_PIN		PINC
	#define SSERIAL_RX_PIN	PINC0
	#define SSERIAL_TX_PIN  PINC1
	/* SSerial RX Interrupt */
	#define SSERIAL_PCIE    PCIE1
	#define SSERIAL_PCMSK	PCMSK1
	#define SSERIAL_PCINT	PCINT8
	#define SSERIAL_PCINT_VECT PCINT1_vect
	#define SSERIAL_PCINT_IF PCIF1
	/* SSerial Timer Settings */
	#if defined HAS_16MHZ_CLOCK
		#define SSERIAL_TIMER_DISABLE() (TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20)))
		#define SSERIAL_TIMER_ENABLE()	(TCCR2B |=  (1<<CS21) | (1<<CS20))) ) //Prescale 32 - 2us
		/* Timerlänge Bits (16000000 / 32 * 1 / 38400 = 13,02) (HZ/Prescaler*1/Baud)
		52=9600baud / 38400 nicht probiert */
		#define SSERIAL_TIMER_1BIT()			(OCR2A = 52) 
		#define SSERIAL_TIMER_15BIT()			(OCR2A = 78) 
		#define SSERIAL_TIMER_RESET()			(TCNT2 = 0)
	#else
		#define SSERIAL_TIMER_DISABLE() (TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20)))
		#define SSERIAL_TIMER_ENABLE()	(TCCR2B |=  (1<<CS21) ) //Prescale 8 - 1us
		/* Timerlänge Bits (8000000 / 8 * 1 / 38400 = 26,04) (HZ/Prescaler*1/Baud)
		104=9600baud / 38400 zu schnell... */
		#define SSERIAL_TIMER_1BIT()			(OCR2A = 104) 
		#define SSERIAL_TIMER_15BIT()			(OCR2A = 156) 
		#define SSERIAL_TIMER_RESET()			(TCNT2 = 0)
	#endif
#endif


/* HAS_MBUS requires about 1kB RAM, if you want to use it you
   should consider disabling other unneeded features
   to avoid stack overflows
*/
//#define HAS_MBUS

/* Intertechno Senden einschalten */
#  define HAS_INTERTECHNO
#  define HAS_TX3
#  define HAS_UNIROLL

#  define HAS_MEMFN
#  define HAS_SOMFY_RTS
#  define HAS_RFNATIVE


#if defined (nanoCUL433)
/* Intertechno Empfang einschalten */
#  define HAS_IT
#  define HAS_TCM97001
#  define HAS_MANCHESTER
/* Won't fit with SSerial Stacking */
#ifndef HAS_SSERIAL
#  define HAS_REVOLT
#  define HAS_HOMEEASY
#  define HAS_BELFOX
#endif
#endif

#if defined (nanoCUL868)

#  define HAS_ASKSIN_FUP
#  define HAS_MORITZ
#  define HAS_RWE
#  define HAS_ESA
//#  define HAS_HOERMANN
#  define HAS_HMS
#  define OFF_LACROSSE_HMS_EMU          // if you like HMS emulation for LaCrosse temp devices
#endif

#endif
