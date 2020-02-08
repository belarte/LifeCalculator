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
	ConstExpression(int i);

	life::Inputs evaluate() override;

private:
	int m_value;
};

} // end namespace
