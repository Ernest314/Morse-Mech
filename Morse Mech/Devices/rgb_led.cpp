#include "rgb_led.h"

RGB_LED::RGB_LED(LED LED_R, LED LED_G, LED LED_B) :
	m_R(LED_R),
	m_G(LED_G),
	m_B(LED_B)
{ }

void RGB_LED::updateLEDs(uint16_t count) {
	m_R.updateLED(count);
	m_G.updateLED(count);
	m_B.updateLED(count);
}

void RGB_LED::setBrightness(Color color) {
	m_R.setBrightness(color.R_raw());
	m_G.setBrightness(color.G_raw());
	m_B.setBrightness(color.B_raw());
}
