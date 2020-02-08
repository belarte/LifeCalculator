#include "parser.h"
#include "life/board.h"
#include "life/create.h"
#include "life/rle.h"
#include "utils/parser.h"

namespace expression {

std::unique_ptr<Expression> Parser::parse(const std::string& input) {
	utils::Parser parser{input};
	parser.readInt();
	int value = parser.lastInt();
	return std::make_unique<ConstExpression>(value);
}

} // end namespace
