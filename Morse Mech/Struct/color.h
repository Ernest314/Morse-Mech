#ifndef _COLOR_H_
#define _COLOR_H_

#include <math.h>
#include <stdint.h>

class Color {
public:
	// TODO: turn this into a static lookup table(?)
	// (Is there enough space?)
	static constexpr float gamma = 2.8;
	
private:
	uint16_t m_R_raw, m_B_raw, m_G_raw;
	
public:
	Color(uint16_t R_in, uint16_t G_in, uint16_t B_in);
	uint16_t gamma_correct(uint16_t val);
	
	uint16_t R_raw() { return m_R_raw; }
	uint16_t G_raw() { return m_G_raw; }
	uint16_t B_raw() { return m_B_raw; }
};

#endif // _COLOR_H_
