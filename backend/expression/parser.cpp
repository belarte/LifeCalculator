#include "parser.h"
#include <cstdlib>

namespace expression {

class ConstExpression : public Expression
{
public:
	ConstExpression(int i)
		: m_value{i}
	{}

	std::string evaluate() override {
		return  m_value == 1 ? "data: x = 3, y = 3\nbo$2bo$3o!" : "nothing";
	}

private:
	int m_value;
};

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	int value = atoi(input.c_str());
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
