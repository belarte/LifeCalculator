#include "life/board.h"
#include <memory>
#include <string>

namespace expression {

class Expression
{
public:
	virtual life::Inputs evaluate() = 0;
};

class Parser
{
public:
	std::unique_ptr<Expression> parse(const std::string&);
};

} // end namespace
