#include "expression.h"
#include "life/rle.h"

namespace expression {

ConstExpression::ConstExpression(uint8_t i)
		: m_value{i}
	{}

life::Inputs ConstExpression::evaluate() {
	life::Input input{life::rle::Glider, life::Coords{ {0, 0} }};
	return  m_value == 1 ? life::Inputs{ {input} } : life::Inputs{};
}

} // end namespace
