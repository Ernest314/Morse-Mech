#include "timer.h"

// These global variables are NOT simply defined in the header, to
// prevent any #includes from also acquiring access to the `count_global`
// variable (making this variable effectively local).

static volatile uint64_t count_global = 0;
static volatile bool is_running = false;
// TODO: Should we use a bool here or mess with the interrupt registers?
// If so, where should that be handled? (Here or in "init.cpp"?)

ISR(TIMER0_OVF_vect) {
	if (is_running)	{ count_global++; }
}

void Timer::global_start()	{ is_running = true; }
void Timer::global_pause()	{ is_running = false; }
void Timer::global_stop() {
	global_pause();
	clear_global();
}

uint64_t Timer::get_global() {
	uint64_t total = 0;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		total = TCNT1 + (count_global << 16);
	}
	return total;
}
bool Timer::get_global_did_overflow() {
	// 64 bits -> 8 bytes, TCNT has 2 bytes, 6 bytes worth of mask
	return (count_global > 0xFFFFFFFFFFFF) ? true : false;
}
void Timer::clear_global() {
	// TCNT1 is a 16-bit register; requires ATOMIC
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		TCNT1 = 0;
	}
	count_global = 0;
}
void Timer::set_global(uint64_t count) {
	TCNT1 = count & 0xFFFF;		// reset TCNT1 register
	count_global = count >> 16;	// reset global counter
}

Timer::Timer(uint64_t timestamp_begin) :
	m_timestamp(timestamp_begin) { }

double Timer::get_sec() {
	return (double)get_global() / ((double)1 / F_CPU);
}
