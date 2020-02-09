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

TEST(OutputExpressionEvaluatesTo, correct_output_with_non_zero_input)
{
	auto expr = OutputExpression(std::make_unique<ConstExpression>(135));
	auto inputs = expr.evaluate();

	EXPECT_THAT(inputs, SizeIs(2));

	for (const auto& input : inputs) {
		if (input.pattern == life::rle::Eater) {
			EXPECT_THAT(input.offsets, SizeIs(8));
			EXPECT_THAT(input.offsets, UnorderedElementsAre(
				life::Coord{1, 4},
				life::Coord{12, 4},
				life::Coord{23, 4},
				life::Coord{34, 4},
				life::Coord{45, 4},
				life::Coord{56, 4},
				life::Coord{67, 4},
				life::Coord{78, 4}
			));
		} else if (input.pattern == life::rle::Glider) {
			EXPECT_THAT(input.offsets, SizeIs(4));
			EXPECT_THAT(input.offsets, UnorderedElementsAre(
				life::Coord{0, 0},
				life::Coord{11, 0},
				life::Coord{22, 0},
				life::Coord{77, 0}
			));
		} else {
			FAIL() << "Unexpected input pattern";
		}
	}
}

// TODO test for non-zero input
