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

OutputExpression::OutputExpression(std::unique_ptr<Expression> expr) :
	m_input{std::move(expr)},
	m_offset{11}
{}

life::Inputs OutputExpression::evaluate()
{
	life::Coords offsets;
	for (uint8_t i = 0; i<8; ++i) {
		offsets.push_back(life::Coord{uint8_t(m_offset * i), 0});
	}

	return  life::Inputs{ { life::Input{ life::rle::Eater, offsets } } };
}

} // end namespace
