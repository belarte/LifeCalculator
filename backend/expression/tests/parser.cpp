#include "../parser.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(ParserThrowsException, when_number_is_larger_than_8_bits)
{
	EXPECT_THROW(Parser{}.parse("256"), InvalidNumber);
}
