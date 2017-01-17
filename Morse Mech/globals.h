#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdint.h>
#include "Data/queue.h"
#include "Struct/keycombo.h"
#include "Struct/morse.h"

extern volatile queue<MorseBit> queue_input;
extern volatile queue<KeyCombo> queue_keycombos;

#endif	// _GLOBALS_H_
