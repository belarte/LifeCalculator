#include "../parser.h"

#include <typeinfo>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(ParserThrowsException, when_number_is_larger_than_8_bits)
{
	EXPECT_THROW(Parser{}.parse("256"), InvalidNumber);
}

TEST(ParserReturns, concrete_expression_for_number)
{
	auto expr = Parser{}.parse("123");

	EXPECT_EQ(typeid(*expr.get()), typeid(ConstExpression));
}
