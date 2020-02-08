#include "life/types.h"

namespace expression {

class Expression
{
public:
	virtual life::Inputs evaluate() = 0;
};

class ConstExpression : public Expression
{
public:
	ConstExpression(uint8_t i);

	life::Inputs evaluate() override;

private:
	uint8_t m_value;
	uint8_t m_spacing;
};

} // end namespace
