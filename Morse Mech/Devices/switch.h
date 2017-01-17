#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <stdint.h>
#include <avr/io.h>	// TCNT1 is used as the debounce timer

// TODO: Make it so this doesn't require exclusive control of Timer1
class Switch {
public:
	static const int msec_per_sec = 1000;
	static const int debounce_msec_cherry = 5;
	// Cherry cites a <= 5 msec bounce time @ 16 in/sec.
	
	static const uint64_t debounce_count_cherry =
		((float)debounce_msec_cherry / msec_per_sec) / ((float)1 / F_CPU);

private:
	volatile uint8_t* PINx;
	int PINxN;
	uint64_t debounce_count_min;	// we *want* an "uninitialized" warning
	
	bool m_is_closed = false;
	bool m_is_closed_prev = false;
	uint64_t m_debounce_count = 0;
	uint16_t m_timestamp = 0;
	
	bool is_debouncing = false;
	bool is_closed_raw = false;
	bool is_closed_raw_prev = false;
	
public:
	Switch(	volatile uint8_t* PINx,
			int PINxN,
			uint64_t debounce_count = debounce_count_cherry );
	
	void update();
	
	bool is_closed()		{ return m_is_closed; }
	bool is_closed_prev()	{ return m_is_closed_prev; }
	bool is_debounced();

private:
	void transition();
};

#endif	// _SWITCH_H_
