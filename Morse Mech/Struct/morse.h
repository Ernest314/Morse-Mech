#ifndef _MORSE_H_
#define _MORSE_H_

#include <stdint.h>
#include "morsestatus.h"
#include "keycombo.h"
#include "../Data/queue.h"
#include "../LUFA/Drivers/USB/USB.h"

struct KeyCombo;
// TODO: take another look at all includes; see if only forward declare is needed

enum class MorseBit {
	Unknown	= 0,
	Dot		= 1,
	Dash	= 2
};

KeyCombo popScancode(volatile queue<MorseBit>& data);

#endif	// _MORSE_H_
