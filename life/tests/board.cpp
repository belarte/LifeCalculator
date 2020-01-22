#include "../board.h"

#include "gtest/gtest.h"

using namespace life;
using namespace testing;

Coords Eater = {
	{3, 0}, {4, 0}, {7, 0}, {8, 0},
	{0, 1}, {4, 1}, {7, 1}, {8, 1},
	{0, 2}, {1, 2}, {2, 2}, {3, 2},
	{0, 4}, {1, 4},
	{0, 5}, {1, 5}
};

Coords Glider = {
	{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}
};

Board prepareBoard(unsigned int width, unsigned int height, const Coords& coords)
{
	auto unit = Board{width, height};
	for (const auto& c : coords) {
		unit.setAlive(c);
	}
	return unit;
}

TEST(BoardSimulation, simulate_does_not_change_board_with_still_pattern)
{
	auto unit = prepareBoard(9, 6, Eater);
	unit.simulate();

	for (size_t j=0; j<6; ++j) {
		for (size_t i=0; i<9; ++i) {
			bool isAlive = std::find(Eater.begin(), Eater.end(), Coord{i, j}) != Eater.end();
			EXPECT_EQ(isAlive, unit.isAlive({i, j}));
		}
	}
}

TEST(BoardSimulation, simulate_changes_change_board_with_glider_pattern)
{
	Coords expected = { {0, 1}, {2, 1}, {1, 3}, {1, 2}, {2, 2} };

	auto unit = prepareBoard(4, 4, Glider);
	unit.simulate();

	for (size_t j=0; j<4; ++j) {
		for (size_t i=0; i<4; ++i) {
			bool isAlive = std::find(expected.begin(), expected.end(), Coord{i, j}) != expected.end();
			EXPECT_EQ(isAlive, unit.isAlive({i, j}));
		}
	}
}

TEST(BoardSimulation, multiple_simulate_changes_change_board_with_glider_pattern)
{
	Coords expected = { {2, 1}, {3, 2}, {1, 3}, {2, 3}, {3, 3} };

	auto unit = prepareBoard(4, 4, Glider);
	unit.simulate();
	unit.simulate();
	unit.simulate();
	unit.simulate();

	for (size_t j=0; j<4; ++j) {
		for (size_t i=0; i<4; ++i) {
			bool isAlive = std::find(expected.begin(), expected.end(), Coord{i, j}) != expected.end();
			EXPECT_EQ(isAlive, unit.isAlive({i, j})) << Coord{i, j} << " is " << isAlive;
		}
	}
}
