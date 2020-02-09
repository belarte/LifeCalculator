#include "expression.h"
#include "life/rle.h"

namespace expression {

ConstExpression::ConstExpression(uint8_t i) :
	m_value{i},
	m_offset{11}
{}

life::Inputs ConstExpression::evaluate() {
	if (m_value == 0) {
		return life::Inputs{};
	}

	life::Coords offsets;
	for (uint8_t i = 0; i<8; ++i) {
		if (((m_value >> i) & 1) > 0) {
			offsets.push_back(life::Coord{uint8_t(m_offset * i), 0});
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
	life::Inputs output;

	auto offset = life::Coord{0, 0};
	auto inputs = m_input->evaluate();
	if (!inputs.empty()) {
		offset = life::Coord{1, 4};
		for (const auto& input : inputs) {
			output.push_back(input);
		}
	}

	life::Coords offsets;
	for (uint8_t i = 0; i<8; ++i) {
		offsets.push_back(life::Coord{uint8_t(m_offset * i), 0} + offset);
	}

	output.push_back(life::Input{ life::rle::Eater, offsets});
	return output;
}

} // end namespace
