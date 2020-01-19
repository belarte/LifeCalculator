#include "../types.h"

#include "gtest/gtest.h"

using namespace life;

TEST(CoordOperations, addition)
{
	EXPECT_EQ((Coord{4, 5}), (Coord{1, 3} + Coord{3, 2}));
	EXPECT_EQ((Coord{4, 5}), (Coord{4, 5} + Coord{0, 0}));
}

TEST(CoordOperations, substraction)
{
	EXPECT_EQ((Coord{1, 3}), (Coord{4, 5} - Coord{3, 2}));
	EXPECT_EQ((Coord{4, 5}), (Coord{4, 5} - Coord{0, 0}));
}
