#ifndef _RGB_LED_H_
#define _RGB_LED_H_

#include <stdint.h>
#include "led.h"
#include "../Struct/color.h"

// NOTE: like `LED`, must be "clocked" when calling `updateLED`.
class RGB_LED {
private:
	LED m_R, m_G, m_B;
	
public:
	RGB_LED(LED LED_R, LED LED_G, LED LED_B);
	void updateLEDs(uint16_t count);
	
	void setBrightness(Color color);
	
};

#endif // _RGB_LED_H_
