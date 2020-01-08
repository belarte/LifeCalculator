#include "../board.h"
#include "../rle.h"
#include "gtest/gtest.h"

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

using namespace life;

TEST(BoardCreation, creates_with_correct_dimensions)
{
	auto board = life::FromRLE("x = 15, y = 6\n!");

	ASSERT_EQ(15, board->width());
	ASSERT_EQ(6, board->height());
}

TEST(BoardCreation, create_with_pattern)
{
	auto board = life::FromRLE(Glider);

	std::vector<std::pair<Coord, bool>> dataset = {
		{{0, 0}, false},
		{{1, 0}, true},
		{{2, 0}, false},
		{{0, 1}, false},
		{{1, 1}, false},
		{{2, 1}, true},
		{{0, 2}, true},
		{{1, 2}, true},
		{{2, 2}, true}
	};

	for (auto& data : dataset) {
		EXPECT_EQ(data.second, board->isAlive(data.first));
	}
}
