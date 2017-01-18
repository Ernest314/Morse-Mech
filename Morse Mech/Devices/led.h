#ifndef _LED_H_
#define _LED_H_

#include <stdint.h>

// NOTE: must be "clocked" when calling `updateLED`.
class LED {
private:
	volatile uint8_t* m_port;
	int m_mask_i;
	uint16_t m_brightness = 0;
	
public:
	LED(volatile uint8_t* port, int mask_i, uint16_t brightness=0);
	void updateLED(uint16_t count);
	
	void setBrightness(uint16_t brightness) { m_brightness = brightness; }
	uint16_t getBrightness() { return m_brightness; }
};

#endif // _LED_H_
