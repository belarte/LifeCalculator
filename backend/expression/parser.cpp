#include "parser.h"
#include "life/board.h"
#include "life/create.h"
#include "life/rle.h"

namespace expression {

class ConstExpression : public Expression
{
public:
	ConstExpression(int i)
		: m_value{i}
	{}

	life::Board evaluate() override {
		life::Input input{life::rle::Glider, life::Coords{ {0, 0} }};
		return  m_value == 1 ? life::Create({input}, life::FromRLE) : life::Board{0, 0};
	}

private:
	int m_value;
};

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	int value = atoi(input.c_str());
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
