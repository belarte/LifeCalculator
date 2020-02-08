#include "expression.h"

#include <memory>
#include <string>

namespace expression {

class Parser
{
public:
	std::unique_ptr<Expression> parse(const std::string&);
};

} // end namespace
