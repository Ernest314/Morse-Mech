#include "init.h"

// All page numbers ("p###") refer to the complete datasheet.
// TODO: setup watchdog stuff, power stuff
// TODO: fuses for clock settings

void init_DDR();
void init_PORT();
void init_SPI();
void init_timer16();
void init_ext_interrupt();

void init() {
	init_DDR();
	init_PORT();
	init_SPI();
	init_timer16();			// NOTE: custom timer needs to be started separately
	init_ext_interrupt();	// NOTE: sei() needs to be called separately
}

void init_DDR() {
	// DDRx: 1 = output, 0 = input
	DDRB =
		0 << DDB0 |
		1 << DDB1 |	// SCLK
		1 << DDB2 |	// MOSI
		0 << DDB3 |	// MISO
		1 << DDB4 |
		1 << DDB5 |
		1 << DDB6 |
		0 << DDB7;
	DDRC =
		0 << DDC0 |
		0 << DDC1 |
		0 << DDC2 |
		0 << DDC4 |
		0 << DDC5 |
		0 << DDC6 |
		0 << DDC7;
	DDRD =
		0 << DDD0 |
		0 << DDD1 |
		0 << DDD2 |
		1 << DDD3 |	// SS_EEPROM
		0 << DDD4 |
		1 << DDD5 |
		1 << DDD6 |
		1 << DDD7;
}

void init_PORT() {
	// Writing 1 to input pins enables pull-up
	PORTB =
		0 << PORTB0 |
		0 << PORTB1 |	// No SPI ports should be pulled up.
		0 << PORTB2 |	// ^
		0 << PORTB3 |	// ^
		0 << PORTB4 |
		0 << PORTB5 |
		0 << PORTB6 |
		0 << PORTB7;
	PORTC =
		0 << PORTC0 |
		0 << PORTC1 |	// 'RESET has an external pull-up
		0 << PORTC2 |	
		0 << PORTC4 |	
		0 << PORTC5 |	
		0 << PORTC6 |	
		0 << PORTC7;
	PORTD =
		1 << PORTD0 |	// pull up keyswitch input
		0 << PORTD1 |
		0 << PORTD2 |
		1 << PORTD3 |	// "pull up" SS_EEPROM (output)
		0 << PORTD4 |
		0 << PORTD5 |
		0 << PORTD6 |
		0 << PORTD7;
}

void init_SPI() {
	// If PRSPI is set, the clock to the SPI interface is stopped.
	PRR0 &= ~(1 << PRSPI);	// This defaults to 0; we're clearing it just in case.
	SPCR =
		1 << SPIE |	// enable SPI interrupts
		1 << SPE  |	// enable SPI
		0 << DORD |	// MSB transmitted first (big-endian)
		1 << MSTR |	// master SPI mode
		0 << CPOL |	// setting CPOL/CPHA = 1/1 also works;
		0 << CPHA |	// the only difference is in standby mode (not used)
		0 << SPR1 |	// f_osc / 2 @ SPR1/SPR0 = 0/0, with SPI2X high
		0 << SPR0 ;	// max 20MHz @ 5V (10MHz @ 3.3V)
	// F_SCLK = 8MHz @ F_CPU = 16 MHz
	// For other SPR0/SPR1 effects, see Table 17-5 (p146).
	SPSR |= 1 << SPI2X;	// works by changing the SPI clock to 2 CPU cycles
}

void init_timer16() {
	// ICNCn, ICESn, and WGMn[3:2] all init to 0 (p133).
	// For other CSn[2:0] combinations, see Table 16-5 (p133).
	TCCR1B =
		0 << CS12 |
		0 << CS11 |
		1 << CS10;
		// CS1[2:0] = {001} sets the clock to clk_IO (no prescaling).
	TIMSK1 |= 1 << TOIE1;	// enable overflow interrupt
}

void init_ext_interrupt() {
	// External pin interrupts
	EICRA |= 1 << ISC00; EICRA &= ~(1 << ISC01);
		// ISC01/ISC00 = 0/1: interrupt on either edge.
		// See Table 13-1 for other effects (p85).
	EIMSK |= 1 << INT0;	// keyswitch
}
