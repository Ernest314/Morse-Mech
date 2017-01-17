#include "morse.h"

KeyCombo popScancode(volatile queue<MorseBit>& data) {
	// TODO: max length is 10 bits I think? 9+1 (+1 to denote start)
	uint16_t buffer = 0;
	while (!data.empty()) {
		buffer += 0b1;	// Makes sure we know where the encoding starts
		switch (data.back()) {
			case MorseBit::Dot :
				buffer <<= 1;
				buffer += 0b0;
				break;
			case MorseBit::Dash :
				buffer <<= 1;
				buffer += 0b1;
				break;
			case MorseBit::Unknown :
				// TODO: do something else? add default case?
				break;
		}
		data.pop();
	}
	// TODO: It might even be better to place this into the queue directly.
	
	// 0 = padding, 1 = start, 0 = dot, 1 = dash
	uint8_t scancode = HID_KEYBOARD_SC_ERROR_UNDEFINED;
	uint8_t modifier = HID_KEYBOARD_MODIFIER_NONE;
	MorseStatus status = MorseStatus::None;
	switch (buffer) {
		// Letters
		// NOTE: All characters are in upper-case by design!
		case 0b0000000101 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_A; break;
		case 0b0000011000 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_B; break;
		case 0b0000011010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_C; break;
		case 0b0000001100 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_D; break;
		case 0b0000000010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_E; break;
		case 0b0000010010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_F; break;
		case 0b0000001110 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_G; break;
		case 0b0000010000 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_H; break;
		case 0b0000000100 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_I; break;
		case 0b0000010111 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_J; break;
		case 0b0000001101 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_K; break;
		case 0b0000010100 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_L; break;
		case 0b0000000111 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_M; break;
		case 0b0000000110 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_N; break;
		case 0b0000001111 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_O; break;
		case 0b0000010110 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_P; break;
		case 0b0000011101 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_Q; break;
		case 0b0000001010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_R; break;
		case 0b0000001000 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_S; break;
		case 0b0000000011 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_T; break;
		case 0b0000001001 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_U; break;
		case 0b0000010001 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_V; break;
		case 0b0000001011 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_W; break;
		case 0b0000011001 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_X; break;
		case 0b0000011011 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_Y; break;
		case 0b0000011100 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_Z; break;
		
		// Numbers
		case 0b0000101111 : scancode = HID_KEYBOARD_SC_1_AND_EXCLAMATION;	break;
		case 0b0000100111 : scancode = HID_KEYBOARD_SC_2_AND_AT;			break;
		case 0b0000100011 : scancode = HID_KEYBOARD_SC_3_AND_HASHMARK;		break;
		case 0b0000100001 : scancode = HID_KEYBOARD_SC_4_AND_DOLLAR;		break;
		case 0b0000100000 : scancode = HID_KEYBOARD_SC_5_AND_PERCENTAGE;	break;
		case 0b0000110000 : scancode = HID_KEYBOARD_SC_6_AND_CARET;			break;
		case 0b0000111000 : scancode = HID_KEYBOARD_SC_7_AND_AMPERSAND;		break;
		case 0b0000111100 : scancode = HID_KEYBOARD_SC_8_AND_ASTERISK;		break;
		case 0b0000111110 : scancode = HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS; break;
		case 0b0000111111 : scancode = HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS; break;
		
		// Punctuation
		case 0b0000110010 : scancode = HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK;		break;
		case 0b0001011110 : scancode = HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE;		break;
		case 0b0001101010 : scancode = HID_KEYBOARD_SC_SEMICOLON_AND_COLON;			break;
		case 0b0001010101 : scancode = HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN;	break;
		case 0b0001110011 : scancode = HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN;	break;
		case 0b0001100001 : scancode = HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE;		break;
		case 0b0001010010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE;	break;
		case 0b0001111000 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_SEMICOLON_AND_COLON;		break;
		case 0b0001001100 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK;	break;
		case 0b0000011110 :	// Intentional fall-through: <MN> was "carried over from American landline telegraphy code"
		case 0b0001101011 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_1_AND_EXCLAMATION;		break; // <KW>
		case 0b0001011010 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_2_AND_AT;				break; // <AC>
		case 0b0010001001 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_4_AND_DOLLAR;			break; // <SX>
		case 0b0000110110 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS; break;
		case 0b0001101101 : modifier = HID_KEYBOARD_MODIFIER_SHIFT; scancode = HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS; break;
		
		// Prosigns
		case 0b0000101010 : modifier = HID_KEYBOARD_MODIFIER_CTRL; scancode = HID_KEYBOARD_SC_ENTER; break; // <AR>: new page
		case 0b0000010101 : scancode = HID_KEYBOARD_SC_ENTER;		break;	// <AA>: new line
		case 0b0001100111 : scancode = HID_KEYBOARD_SC_CAPS_LOCK;	break;	// <NJ>: shift to Wabun code
		case 0b0100000000 : scancode = HID_KEYBOARD_SC_BACKSPACE;	break;	// <HH>: error
		case 0b0000110001 : status = MorseStatus::Section;	break;			// <BT>: new paragraph (CR-LF-LF)
		case 0b0000101000 : status = MorseStatus::Wait;		break;			// <AS>: wait
		case 0b1000111000 : status = MorseStatus::Reset;	break;			// <SOS>: reset device
		
		default : status = MorseStatus::Error; break;
	}
	return KeyCombo(scancode, modifier, status);
}
