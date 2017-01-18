#include "color.h"

Color::Color(uint16_t R_in, uint16_t G_in, uint16_t B_in) :
	m_R_raw(gamma_correct(R_in)),
	m_B_raw(gamma_correct(B_in)),
	m_G_raw(gamma_correct(G_in))
{ }

uint16_t gamma_correct(uint16_t val) {
	return round(pow(val, Color::gamma));
}
