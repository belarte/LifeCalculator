#include "life/types.h"

#include <memory>

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
	uint8_t m_offset;
};

class OutputExpression : public Expression
{
public:
	OutputExpression(std::unique_ptr<Expression> expr);

	life::Inputs evaluate() override;

private:
	std::unique_ptr<Expression> m_input;
	uint8_t m_offset;
};

} // end namespace
