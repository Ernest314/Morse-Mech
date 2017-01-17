#ifndef _TIMER_H_
#define _TIMER_H_

// This should be taken care of in the project config,
// but we're setting it here just in case.
#ifndef F_CPU
#error "F_CPU not defined."
#endif

#include <stdint.h>			// all timers are uint64_t
#include <avr/interrupt.h>	// the global timer is updated via ISR
#include <util/atomic.h>	// timers (uint64_t) need to update safely

class Timer {
public:
	static const int msec_per_sec	= 1000;
	static const int usec_per_msec	= 1000;
	static const int nsec_per_usec	= 1000;
private:
	uint64_t m_timestamp;
		
public:
	// NOTE: Interrupts must be enabled elsewhere before timer will work (`sei()`).
	static void global_start();
	static void global_pause();
	static void global_stop();
		
	static uint64_t get_global();
	static bool get_global_did_overflow();
	static void clear_global();
	static void set_global(uint64_t count);
	
	Timer(uint64_t timestamp_begin = Timer::get_global());
	void set_begin(uint64_t timestamp_begin = Timer::get_global())
		{ m_timestamp = timestamp_begin; }
		
	// NOTE: The get_sec() function is the fastest and most accurate one.
	// Other units of time provided only for convenience--try to use
	// get_sec() wherever possible.
	double get_sec();
	double get_msec()	{ return (get_sec() / 1000); }
	double get_usec()	{ return (get_msec() / 1000); }
	double get_nsec()	{ return (get_usec() / 1000); }
		
	uint64_t get_count()	{ return Timer::get_global() - m_timestamp; }
};

#endif	// _TIMER_H_
