#include "../expression.h"
#include "life/rle.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(ConstExpressionEvatuatesTo, empty_inputs_when_input_is_zero)
{
	auto expr = ConstExpression{0};
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, IsEmpty());
}

TEST(ConstExpressionEvatuatesTo, input_with_one_glider_and_no_offset)
{
	auto expr = ConstExpression{1};
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, SizeIs(1));
	EXPECT_EQ(inputs[0].pattern, life::rle::Glider);
	EXPECT_THAT(inputs[0].offsets, SizeIs(1));
	EXPECT_THAT(inputs[0].offsets[0], Eq(life::Coord{0, 0}));
}

TEST(ConstExpressionEvatuatesTo, correct_input_for_large_number)
{
	auto expr = ConstExpression{210};
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, SizeIs(1));
	EXPECT_EQ(inputs[0].pattern, life::rle::Glider);
	EXPECT_THAT(inputs[0].offsets, SizeIs(4));
	EXPECT_THAT(inputs[0].offsets, UnorderedElementsAre(
		life::Coord{11, 0},
		life::Coord{44, 0},
		life::Coord{66, 0},
		life::Coord{77, 0}
	));
}

TEST(OutputExpressionEvaluatesTo, eight_eaters_with_input_0)
{
	auto expr = OutputExpression(std::make_unique<ConstExpression>(0));
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, SizeIs(1));
	EXPECT_EQ(inputs[0].pattern, life::rle::Eater);
	EXPECT_THAT(inputs[0].offsets, SizeIs(8));
	EXPECT_THAT(inputs[0].offsets, UnorderedElementsAre(
		life::Coord{0, 0},
		life::Coord{11, 0},
		life::Coord{22, 0},
		life::Coord{33, 0},
		life::Coord{44, 0},
		life::Coord{55, 0},
		life::Coord{66, 0},
		life::Coord{77, 0}
	));
}
