#include "parser.h"
#include "life/board.h"
#include "life/create.h"
#include "life/rle.h"
#include "utils/parser.h"

namespace expression {

class ConstExpression : public Expression
{
public:
	ConstExpression(int i)
		: m_value{i}
	{}

	life::Inputs evaluate() override {
		life::Input input{life::rle::Glider, life::Coords{ {0, 0} }};
		return  m_value == 1 ? life::Inputs{ {input} } : life::Inputs{};
	}

private:
	int m_value;
};

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	utils::Parser parser{input};
	parser.readInt();
	int value = parser.lastInt();
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
