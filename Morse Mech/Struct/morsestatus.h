#ifndef _MORSESTATUS_H_
#define _MORSESTATUS_H_

enum class MorseStatus {
	Error	= -1,
	Unknown	= 0,
	None	= 1,
	Reset	= 2,
	Wait	= 3,
	Sleep	= 4,
	Section	= 5
};

#endif	// _MORSESTATUS_H_
