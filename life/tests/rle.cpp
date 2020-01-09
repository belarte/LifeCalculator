#include "../board.h"
#include "../rle.h"
#include "gtest/gtest.h"

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

namespace life {

bool operator==(const Coord& left, const Coord& right)
{
	return left.x == right.x && left.y == right.y;
}

}

using namespace life;

TEST(FromRLE, create_with_pattern)
{
	auto coords = FromRLE(Glider);

	std::vector<Coord> expected = {
		{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}
	};

	EXPECT_EQ(expected.size(), coords.size());
	for (unsigned int i=0; i<expected.size(); ++i) {
		EXPECT_EQ(expected[i], coords[i]);
	}
}
