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

#define SW_KEY_PINX  PIND
#define SW_KEY_PINXN PIND0

void init();

#endif	// _SETUP_H_
