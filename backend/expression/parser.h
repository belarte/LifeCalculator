#pragma once

#include "expression.h"

#include <memory>
#include <string>

namespace expression {

class InvalidNumber : public std::exception
{
public:
	InvalidNumber(int n);
	const char* what() const throw() override;

private:
	int m_value;
};

class Parser
{
public:
	std::unique_ptr<Expression> parse(const std::string&);
};

} // end namespace
