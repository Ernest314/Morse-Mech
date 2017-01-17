#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/atomic.h>
#include <util/delay.h>
// No TWI on the ATmega16u2 :(
// ATmega32u4 does seem to have it though--cost issue?

#include "LUFA/Drivers/USB/USB.h"
#include "LUFA/Platform/Platform.h"

#include "Data/queue.h"
#include "Data/vector.h"
#include "Devices/timer.h"
#include "Devices/switch.h"
#include "Struct/keycombo.h"
#include "Struct/morse.h"

#include "init.h"

// TODO: Should "globals.h" and "init.h" be combined?
#include "globals.h"
#include "descriptors.h"
#include "HID.h"

static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

USB_ClassInfo_HID_Device_t Keyboard_HID_Interface;

volatile uint64_t count_delay_dot = 10000;
volatile uint64_t threshold_3u_lower = 25000;
volatile uint64_t threshold_7u_lower = 50000;

const int queue_input_len		= 36;	// Longest prosign is 'SOS; this is enough to store two
const int queue_keycombos_len	= 16;	// TODO: Figure out a logical value for this buffer

MorseBit queue_input_mem[queue_input_len];
KeyCombo queue_keycombos_mem[queue_keycombos_len];

volatile queue<MorseBit> queue_input =
	queue<MorseBit>(queue_input_mem, queue_input_len);
volatile queue<KeyCombo> queue_keycombos =
	queue<KeyCombo>(queue_keycombos_mem, queue_keycombos_len);

enum class Mode {
	Mode_Suspend = 0,
	Mode_Active = 1
};

void push_Morse(bool was_closed, uint64_t code_len);

int main()
{
	init();
	
	Keyboard_HID_Interface.Config.InterfaceNumber			= INTERFACE_ID_Keyboard;
	Keyboard_HID_Interface.Config.ReportINEndpoint.Address	= KEYBOARD_EPADDR;
	Keyboard_HID_Interface.Config.ReportINEndpoint.Size		= KEYBOARD_EPSIZE;
	Keyboard_HID_Interface.Config.ReportINEndpoint.Banks	= 1;
	Keyboard_HID_Interface.Config.PrevReportINBuffer		= PrevKeyboardHIDReportBuffer;
	Keyboard_HID_Interface.Config.PrevReportINBufferSize	= sizeof(PrevKeyboardHIDReportBuffer);
	
	Timer::global_start();
	
	//Mode mode_sys = Mode_Suspend;
	// TODO: turn on caps lock (only send scancode once)
	
	Switch switch_key(&SW_KEY_PINX, SW_KEY_PINXN);
	Timer timer_switch;
	
    while (true) {
		switch_key.update();
		
		if (switch_key.is_closed() != switch_key.is_closed_prev()) {
			timer_switch.set_begin();
		} else {
			bool was_closed = switch_key.is_closed_prev();
			uint64_t code_len = timer_switch.get_count();
			push_Morse(was_closed, code_len);
		}
		
		HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
    }
}

void push_Morse(bool was_closed, uint64_t code_len) {
	if (was_closed) {
		if (code_len < threshold_3u_lower) {
			queue_input.push(MorseBit::Dot);
		} else {
			queue_input.push(MorseBit::Dash);
		}
	} else {
		if (code_len > threshold_3u_lower && code_len < threshold_7u_lower) {
			queue_keycombos.push(popScancode(queue_input));
		}
		if (code_len >= threshold_7u_lower) {
			queue_keycombos.push(popScancode(queue_input));
			queue_keycombos.push(KeyCombo(HID_KEYBOARD_SC_SPACE));
		}
	}
}

//// Keyswitch interrupt
//ISR(INT0_vect) {
	//// Human simple reaction times ("college-age individuals"):
	//// Auditory: ~160 milliseconds / Visual: ~190 milliseconds
	//// --Wikipedia: Mental chronometry
	//// 50 milliseconds seems like a good value for debouncing
	//// TODO: Timer stuff
//}