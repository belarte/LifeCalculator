#include "parser.h"
#include "life/board.h"
#include "life/create.h"
#include "life/rle.h"
#include "utils/parser.h"

#include <sstream>

namespace expression {

InvalidNumber::InvalidNumber(int n)
	: m_value{n}
{}

const char* InvalidNumber::what() const throw() {
	std::ostringstream oss;
	oss << "Invalid number: " << m_value;
	if (m_value < 0)
		oss << " is lower than 0";
	else
		oss << " is greater than 255";
	return oss.str().data();
}

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	utils::Parser parser{input};
	parser.readInt();
	int value = parser.lastInt();
	if (value > 255 || value < 0) {
		throw InvalidNumber(value);
	}
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
