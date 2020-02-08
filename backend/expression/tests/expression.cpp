#include "../expression.h"
#include "life/rle.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(ConcreteExpressionEvatuatesTo, empty_inputs_when_input_is_zero)
{
	auto expr = ConstExpression{0};
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, IsEmpty());
}

TEST(ConcreteExpressionEvatuatesTo, input_with_one_glider_and_no_offset)
{
	auto expr = ConstExpression{1};
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, SizeIs(1));
	EXPECT_EQ(inputs[0].pattern, life::rle::Glider);
	EXPECT_THAT(inputs[0].offsets, SizeIs(1));
	EXPECT_THAT(inputs[0].offsets[0], Eq(life::Coord{0, 0}));
}
