#include "expression.h"
#include "life/rle.h"

namespace expression {

ConstExpression::ConstExpression(uint8_t i) :
	m_value{i},
	m_spacing{5}
{}

life::Inputs ConstExpression::evaluate() {
	if (m_value == 0) {
		return life::Inputs{};
	}

	life::Coords offsets;
	for (uint8_t i = 0; i<8; ++i) {
		if (((m_value >> i) & 1) > 0) {
			offsets.push_back(life::Coord{uint8_t(m_spacing * i), 0});
		}
	}

	return  life::Inputs{ { life::Input{ life::rle::Glider, offsets } } };
}

} // end namespace
