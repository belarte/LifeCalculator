#include "../board.h"
#include "../rle.h"

#include "gtest/gtest.h"

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

const std::string Eater = R"(x = 9, y = 6
3b2o2b2o$o3bo2b2o$4o$$2o$2o!)";

using namespace life;

TEST(FromRLE, create_with_pattern_glider)
{
	auto coords = FromRLE(Glider);

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
	auto coords = FromRLE(Eater);

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
