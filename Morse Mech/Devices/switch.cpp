#include "switch.h"

Switch::Switch(volatile uint8_t* PINx, int PINxN, uint64_t debounce_count) :
	PINx(PINx),
	PINxN(PINxN),
	debounce_count_min(debounce_count),
	m_debounce_count(0),
	m_timestamp(TCNT1)
{ }

void Switch::update() {
	is_closed_raw = (*PINx & (1 << PINxN)) ? true : false;
	
	if (is_closed_raw == is_closed_raw_prev && is_debouncing) {
		m_debounce_count += TCNT1;
		if (TCNT1 <= m_timestamp)
			{ m_debounce_count += 0xFFFF; }
		m_debounce_count -= m_timestamp;
		if (is_debounced()) {
			transition();
			is_debouncing = false;
		}
	} else {
		is_debouncing = true;
		m_debounce_count = 0;
		m_timestamp = TCNT1;
	}
	
	is_closed_raw_prev = is_closed_raw;
}

bool Switch::is_debounced() {
	return (m_debounce_count >= debounce_count_min);
}

void Switch::transition() {
	m_is_closed_prev = m_is_closed;
	m_is_closed = is_closed_raw;
}
