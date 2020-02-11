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

TEST(InputComparison, is_true_for_same_pattern_and_coords)
{
	EXPECT_EQ((Input{"test", Coords{ {0, 0}, {5, 5}}}), (Input{"test", Coords{ {0, 0}, {5, 5}}}));
}

TEST(InputComparison, is_true_for_same_pattern_and_unordered_coords)
{
	EXPECT_EQ((Input{"test", Coords{ {5, 5}, {0, 0}}}), (Input{"test", Coords{ {0, 0}, {5, 5}}}));
}

TEST(InputComparison, is_false_for_different_patterns)
{
	EXPECT_FALSE((Input{"test", {}}) == (Input{"other", {}}));
}

TEST(InputComparison, is_false_for_same_pattern_with_missing_coords)
{
	EXPECT_FALSE((Input{"test", Coords{ {5, 5}, {0, 0}}}) == (Input{"test", Coords{ {5, 5}}}));
}
