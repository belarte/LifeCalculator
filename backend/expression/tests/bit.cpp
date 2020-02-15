#include "../bit.h"
#include "life/types.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(BitConstructs, a_bit_with_inputs)
{
	Bit bit{ life::Inputs{ { "a", life::Coords{ {0,0} } } }, 1 };

	EXPECT_THAT(bit.output(), Eq(life::Inputs{ { "a", life::Coords{ {0,0} } } }));
}

TEST(BitConstructs, a_bit_with_correct_width)
{
	Bit bit{ {}, 3};

	EXPECT_EQ(bit.width(), 3);
}

TEST(BitConstructs, a_bit_from_two_bits)
{
	Bit left{ life::Inputs{
		{ "a", life::Coords{ {0, 0} } },
		{ "b", life::Coords{ {5, 5} } }
	}, 6 };

	Bit right{ life::Inputs{
		{ "a", life::Coords{ {1, 1}, {2, 2} } }
	}, 3 };

	EXPECT_THAT(Bit(left, right), Eq( Bit{ life::Inputs{
		{ "a", life::Coords{ {0, 0}, {1, 1}, {2, 2} } },
		{ "b", life::Coords{ {5, 5} } }
	}, 6 }));
}

TEST(BitConstructs, a_bit_from_two_bits_has_size_of_largest_bit)
{
	Bit left{ {}, 5 };
	Bit right{ {}, 1 };

	EXPECT_EQ(Bit(left, right).width(), 5);
}

TEST(BitManipulation, offset_propagates_to_output)
{
	Bit input{ life::Inputs{
		{ "a", life::Coords{ {0, 0}, {1, 0} } },
		{ "b", life::Coords{ {5, 5}, {10, 10} } }
	}, 11 };

	input.offset({1, 2});

	EXPECT_THAT(input.output(), Eq(life::Inputs{
		{ "a", life::Coords{ {1, 2}, {2, 2} } },
		{ "b", life::Coords{ {6, 7}, {11, 12} } }
	}));
}
