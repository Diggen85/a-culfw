#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>


/* if you are using a CC1101 module for 868MHz disable the next line 
läuft per Makefile*/
#if defined (MFCUL433)
#define HAS_CC1100_433
#endif

/* General SPI Port*/
#define SPI_PORT		PORTB
#define SPI_DDR			DDRB
#define SPI_MISO		6
#define SPI_MOSI		5
#define SPI_SCLK		7


/*CC1100 868MHz*/
#define CC1100_0_CS_DDR			SPI_DDR
#define CC1100_0_CS_PORT          SPI_PORT
#define CC1100_0_CS_PIN			4
/* GD0 */
#define CC1100_0_OUT_DDR			DDRB
#define CC1100_0_OUT_PORT         PORTB
#define CC1100_0_OUT_PIN          1
#define CC1100_0_OUT_IN           PINB
/*#define CCTEMP_MUX              CC1100_OUT_PIN*/
/*GDO2 Rx Interrupt */
#define CC1100_0_IN_DDR			DDRD
#define CC1100_0_IN_PORT          PIND
#define CC1100_0_IN_PIN           2
#define CC1100_0_IN_IN            PIND
#define CC1100_0_INT				INT0
#define CC1100_0_INTVECT          INT0_vect
#define CC1100_0_ISC				ISC00
#define CC1100_0_EICR             EICRA

/*CC1100 443MHz*/
#define CC1100_1_CS_DDR			SPI_DDR
#define CC1100_1_CS_PORT          SPI_PORT
#define CC1100_1_CS_PIN			3
/* GD0 */
#define CC1100_1_OUT_DDR			DDRB
#define CC1100_1_OUT_PORT         PORTB
#define CC1100_1_OUT_PIN          2
#define CC1100_1_OUT_IN           PINB
/*#define CCTEMP_MUX              CC1100_OUT_PIN*/
/*GDO2 Rx Interrupt */
#define CC1100_1_IN_DDR			DDRD
#define CC1100_1_IN_PORT          PIND
#define CC1100_1_IN_PIN           3
#define CC1100_1_IN_IN            PIND
#define CC1100_1_INT				INT1
#define CC1100_1_INTVECT          INT1_vect
#define CC1100_1_ISC				ISC10
#define CC1100_1_EICR             EICRA



/* externe LED  - B0 = optiboot led*/
#define LED_DDR                 DDRD
#define LED_PORT                PORTD
#define LED_PIN                 7



#define BOARD_ID_STR            "MFCUL868"
#define BOARD_ID_STR433         "MFCUL433"

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

//#define HAS_STACKING


#define RCV_BUCKETS            2      //                 RAM: 25b * bucket
#define FULL_CC1100_PA                // PROGMEM:  108b

#define HAS_CC1101_RX_PLL_LOCK_CHECK_TASK_WAIT
#define HAS_CC1101_PLL_LOCK_CHECK_MSG
#define HAS_CC1101_PLL_LOCK_CHECK_MSG_SW

#define HAS_RAWSEND                   //
#define HAS_FASTRF                    // PROGMEM:  468b  RAM:  1b
#define HAS_ASKSIN
#define HAS_TX3
#define HAS_UNIROLL
#define HAS_MEMFN
#define HAS_SOMFY_RTS
#define HAS_RFNATIVE


#if defined (a644CUL433)
/* Intertechno Senden einschalten */
#define HAS_INTERTECHNO
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

/* IR */
#define HAS_IRRX                                //IR Receiption
#define F_INTERRUPTS            15625   // interrupts per second, min: 10000, max: 20000
#define IRMP_PORT               PORTB
#define IRMP_DDR                DDRB
#define IRMP_PIN                PINB
#define IRMP_BIT                0       // use PA2 as IR input on AVR
//#undef  HAS_IRRX

#define HAS_IRTX                                //IR-Transmission
#define IRSND_OCx               IRSND_OC2B          // use OC2A
#ifndef F_INTERRUPTS            
#define F_INTERRUPTS            15625   // interrupts per second, min: 10000, max: 20000
#endif
//#undef  HAS_IRTX

#endif
