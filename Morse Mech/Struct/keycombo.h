#ifndef _KEYCOMBO_H_
#define _KEYCOMBO_H_

#include <stdint.h>
#include "morsestatus.h"
#include "morse.h"
#include "../LUFA/Drivers/USB/USB.h"

#define HID_KEYBOARD_MODIFIER_NONE (0 << 0)
#define HID_KEYBOARD_MODIFIER_SHIFT HID_KEYBOARD_MODIFIER_LEFTSHIFT
#define HID_KEYBOARD_MODIFIER_CTRL  HID_KEYBOARD_MODIFIER_LEFTCTRL
#define HID_KEYBOARD_MODIFIER_ALT   HID_KEYBOARD_MODIFIER_LEFTALT

struct KeyCombo {
public:
	uint8_t key, modifier;
	MorseStatus status;
	
	KeyCombo(
		uint8_t key_in=HID_KEYBOARD_SC_ERROR_UNDEFINED,
		uint8_t modifier_in=HID_KEYBOARD_MODIFIER_NONE,
		MorseStatus status_in=MorseStatus::None ) :
		key(key_in),
		modifier(modifier_in),
		status(status_in)
		{ }
};

#endif	// _KEYCOMBO_H_
