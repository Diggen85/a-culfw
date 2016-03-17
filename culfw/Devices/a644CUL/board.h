#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>


/* if you are using a CC1101 module for 868MHz disable the next line 
läuft per Makefile*/
#if defined (a644CUL433)
#define HAS_CC1100_433
#endif

#define SPI_PORT		PORTB
#define SPI_DDR			DDRB
#define SPI_SS			4
#define SPI_MISO		6
#define SPI_MOSI		5
#define SPI_SCLK		7

#define CC1100_CS_DDR		SPI_DDR
#define CC1100_CS_PORT          SPI_PORT
#define CC1100_CS_PIN		SPI_SS


/* CC1101 GDO0 Tx / Temperature Sensor */
#define CC1100_OUT_DDR		DDRB
#define CC1100_OUT_PORT         PORTB
#define CC1100_OUT_PIN          3
#define CC1100_OUT_IN           PINB
/*#define CCTEMP_MUX              CC1100_OUT_PIN*/


/* CC1101 GDO2 Rx Interrupt */
#define CC1100_IN_DDR		DDRB
#define CC1100_IN_PORT          PINB
#define CC1100_IN_PIN           2
#define CC1100_IN_IN            PINB

#define CC1100_INT				INT2
#define CC1100_INTVECT          INT2_vect
#define CC1100_ISC				ISC20
#define CC1100_EICR             EICRA

/* externe LED  - B0 = optiboot led*/
#define LED_DDR                 DDRB
#define LED_PORT                PORTB
#define LED_PIN                 0



#define BOARD_ID_STR            "a644CUL868"
#define BOARD_ID_STR433         "a644CUL433"

/* define this device as a 433 MHz one */
/* this isn't done like a CUL by reading a port pin but instead a fixed value of 0 for mark433_pin is used */ 
#define MULTI_FREQ_DEVICE
#define MARK433_PIN 			mark433_pin
#define MARK433_BIT             0
extern const uint8_t mark433_pin;

#define HAS_UART
#define UART_BAUD_RATE          38400

#define USART_RX_vect           USART0_RX_vect
#define USART_UDRE_vect         USART0_UDRE_vect

#define TTY_BUFSIZE             128


#define RCV_BUCKETS            2      //                 RAM: 25b * bucket
#define FULL_CC1100_PA                // PROGMEM:  108b
#define HAS_RAWSEND                   //
#define HAS_FASTRF                    // PROGMEM:  468b  RAM:  1b
#define HAS_ASKSIN

/* Intertechno Senden einschalten */
#define HAS_INTERTECHNO



#define HAS_CC1101_RX_PLL_LOCK_CHECK_TASK_WAIT
#define HAS_CC1101_PLL_LOCK_CHECK_MSG
#define HAS_CC1101_PLL_LOCK_CHECK_MSG_SW
/* HAS_MBUS requires about 1kB RAM, if you want to use it you
   should consider disabling other unneeded features
   to avoid stack overflows
*/
//#define HAS_MBUS

#  define HAS_TX3
#  define HAS_UNIROLL

#  define HAS_MEMFN
#  define HAS_SOMFY_RTS
#  define HAS_RFNATIVE


#if defined (a644CUL433)
/* Intertechno Empfang einschalten */
#  define HAS_IT
#  define HAS_REVOLT
#  define HAS_TCM97001
#  define HAS_HOMEEASY
#  define HAS_BELFOX
#  define HAS_MANCHESTER
#endif

#if defined (a644CUL868)
#  define HAS_ASKSIN_FUP
#  define HAS_MORITZ
#  define HAS_RWE
#  define HAS_ESA
//#  define HAS_HOERMANN
#  define HAS_HMS
#  define OFF_LACROSSE_HMS_EMU          // if you like HMS emulation for LaCrosse temp devices
#endif

#endif
