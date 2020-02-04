#include "parser.h"
#include "life/board.h"
#include <cstdlib>

namespace expression {

class ConstExpression : public Expression
{
public:
	ConstExpression(int i)
		: m_value{i}
	{}

	life::Board evaluate() override {
		return  m_value == 1 ? life::Board{1, 1} : life::Board{0, 0};
	}

private:
	int m_value;
};

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	int value = atoi(input.c_str());
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
