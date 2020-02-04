#include <memory>
#include <string>

namespace expression {

class Expression
{
public:
	virtual std::string evaluate() = 0;
};

class Parser
{
public:
	std::unique_ptr<Expression> parse(const std::string&);
};

} // end namespace
