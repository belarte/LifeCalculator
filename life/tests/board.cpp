#include "../create.h"
#include "../board.h"
#include "../rle.h"
#include "gtest/gtest.h"

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

const std::string GospelGlider = R"(x = 36, y = 9
24bo$22bobo$12b2o6b2o12b2o$11bo3bo4b2o12b2o$2o8bo5bo3b2o$2o8bo3bob2o4bobo$10bo5bo7bo$11bo3bo$12b2o!)";

using namespace life;

TEST(BoardCreation, creates_with_dimension_from_pattern)
{
	auto board = life::Create({GospelGlider, {0, 0}}, FromRLE);

	EXPECT_EQ(36, board->width());
	EXPECT_EQ(9, board->height());
}

TEST(BoardCreation, create_with_pattern)
{
	auto board = life::Create({Glider, {0, 0}}, FromRLE);

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
