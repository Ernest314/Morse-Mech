#ifndef _SETUP_H_
#define _SETUP_H_

// This should be taken care of in the project config,
// but we're setting it here just in case.
#ifndef F_CPU
#define F_CPU 16000000UL
#warning "F_CPU not defined in project settings!"
#endif

#include <avr/io.h>

// +--------------+
// |    PINOUT    |
// +--------------+

// PB0 - (I) NC
// PB1 - (O) SCLK
// PB2 - (O) MOSI
// PB3 - (I) MISO
// PB4 - (O) LED_switch_R
// PB5 - (O) LED_switch_G
// PB6 - (O) LED_switch_B
// PB7 - (I) NC

// PC0 - (I) XTAL2
// PC1 - (I) RESET / debugWire
// PC2 - (I) NC
// PC4 - (I) NC
// PC5 - (I) NC
// PC6 - (I) NC
// PC7 - (I) NC

// PD0 - (I) switch_key
// PD1 - (I) NC
// PD2 - (I) NC
// PD3 - (I) SS_EEPROM
// PD4 - (I) NC
// PD5 - (O) LED_indicator_R
// PD6 - (O) LED_indicator_G
// PD7 - (O) LED_indicator_B

// TODO: pull up all unused inputs?

// TODO: Should these be #defines or constants?
// Is there even a good way to have them be constants?
#define SW_KEY_PIN		PIND
#define SW_KEY_MASK		PIND0

#define LED_IND_PORT_R	PORTD
#define LED_IND_PORT_G	PORTD
#define LED_IND_PORT_B	PORTD
#define LED_IND_MASK_R	PORTD5
#define LED_IND_MASK_G	PORTD6
#define LED_IND_MASK_B	PORTD7

#define LED_SW_PORT_R	PORTB
#define LED_SW_PORT_G	PORTB
#define LED_SW_PORT_B	PORTB
#define LED_SW_MASK_R	PORTB4
#define LED_SW_MASK_G	PORTB5
#define LED_SW_MASK_B	PORTB6

void init();

#endif	// _SETUP_H_
