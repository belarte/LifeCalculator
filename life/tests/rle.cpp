#include "../board.h"
#include "../rle.h"

#include "gtest/gtest.h"

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

using namespace life;

TEST(FromRLE, create_with_pattern)
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
