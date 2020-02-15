#include "../bit.h"
#include "life/rle.h"
#include "life/types.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace expression;
using namespace testing;

TEST(BitConstructs, a_bit_with_inputs)
{
	Bit bit{ life::Inputs{ { life::rle::Glider, life::Coords{ {0,0} } } } };

	EXPECT_THAT(bit.output(), Eq(life::Inputs{ { life::rle::Glider, life::Coords{ {0,0} } } }));
}

TEST(BitConstructs, a_bit_from_two_bits)
{
	Bit left{ life::Inputs{
		{ life::rle::Glider, life::Coords{ {0, 0} } },
		{ life::rle::Eater, life::Coords{ {5, 5} } }
	} };

	Bit right{ life::Inputs{
		{ life::rle::Glider, life::Coords{ {1, 1}, {2, 2} } }
	} };

	EXPECT_THAT(Bit(left, right), Eq( Bit{ life::Inputs{
		{ life::rle::Glider, life::Coords{ {0, 0}, {1, 1}, {2, 2} } },
		{ life::rle::Eater, life::Coords{ {5, 5} } }
	} }));
}

TEST(BitManipulation, offset_propagates_to_output)
{
	Bit input{ life::Inputs{
		{ life::rle::Glider, life::Coords{ {0, 0}, {1, 0} } },
		{ life::rle::Eater, life::Coords{ {5, 5}, {10, 10} } }
	} };

	input.offset({1, 2});

	EXPECT_THAT(input.output(), Eq(life::Inputs{
		{ life::rle::Glider, life::Coords{ {1, 2}, {2, 2} } },
		{ life::rle::Eater, life::Coords{ {6, 7}, {11, 12} } }
	}));
}
