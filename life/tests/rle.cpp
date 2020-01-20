#include "../board.h"
#include "../rle.h"

#include "gtest/gtest.h"

using namespace life;

TEST(FromRLE, create_with_pattern_glider)
{
	auto coords = FromRLE(rle::Glider);

	Coords expected = {
		{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}
	};

	EXPECT_EQ(expected.size(), coords.size());
	for (size_t i=0; i<expected.size(); ++i) {
		EXPECT_EQ(expected[i], coords[i]);
	}
}

TEST(FromRLE, create_with_pattern_eater)
{
	auto coords = FromRLE(rle::Eater);

	Coords expected = {
		{3, 0}, {4, 0}, {7, 0}, {8, 0},
		{0, 1}, {4, 1}, {7, 1}, {8, 1},
		{0, 2}, {1, 2}, {2, 2}, {3, 2},
		{0, 4}, {1, 4},
		{0, 5}, {1, 5}
	};

	EXPECT_EQ(expected.size(), coords.size());
	for (size_t i=0; i<expected.size(); ++i) {
		EXPECT_EQ(expected[i], coords[i]);
	}
}
