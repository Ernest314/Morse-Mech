#include "led.h"

LED::LED(volatile uint8_t* port, int mask_i, uint16_t brightness) :
	m_port(port),
	m_mask_i(mask_i),
	m_brightness(brightness)
{ }

void LED::updateLED(uint16_t count) {
	if (count > m_brightness) {
		*m_port &= ~(1 << m_mask_i);
	} else {
		*m_port |= 1 << m_mask_i;
	}
}
