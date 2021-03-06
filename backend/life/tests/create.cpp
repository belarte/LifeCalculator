#include "../create.h"
#include "../board.h"

#include <algorithm>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace life;
using namespace testing;

struct MockGenerator
{
	MOCK_METHOD1(create, Coords(const std::string&));
};

struct BoardCreation : public Test
{
	Inputs irrelevantInput = { {{"some input"}, Coords{{0, 0}}} };
	MockGenerator mockGenerator;
	Generator generator = [&](const std::string& s){ return mockGenerator.create(s); };
};

TEST_F(BoardCreation, create_forwards_parameters_to_generator)
{
	EXPECT_CALL(mockGenerator, create("some input"));

	auto board = life::Create({ {{"some input"}, Coords{{0, 0}}} }, generator);
}

TEST_F(BoardCreation, creates_with_dimension_from_pattern)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {0, 0}, {35, 8} }));

	auto board = life::Create(irrelevantInput, generator);

	EXPECT_EQ(36, board.width());
	EXPECT_EQ(9, board.height());
}

TEST_F(BoardCreation, create_trims_size_when_pattern_does_not_start_at_origin)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {3, 4} }));

	auto board = life::Create(irrelevantInput, generator);

	EXPECT_EQ(1, board.width());
	EXPECT_EQ(1, board.height());
}

TEST_F(BoardCreation, create_trims_size_when_pattern_is_offset)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {0, 0}, {3, 4} }));

	auto board = life::Create({ {{""}, Coords{{1, 2}}} }, generator);

	EXPECT_EQ(4, board.width());
	EXPECT_EQ(5, board.height());
}

TEST_F(BoardCreation, create_with_pattern)
{
	auto dataset = std::vector<Coord>{ {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };

	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} }));

	auto board = life::Create(irrelevantInput, generator);

	for (size_t j=0; j<3; ++j) {
		for (size_t i=0; i<3; ++i) {
			bool isAlive = std::find(dataset.begin(), dataset.end(), Coord{i, j}) != dataset.end();
			EXPECT_EQ(isAlive, board.isAlive({i, j}));
		}
	}
}

TEST_F(BoardCreation, create_with_multiple_patterns_and_offsets_return_board_with_correct_size)
{
	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {0, 0}, {3, 4} }))
		.WillOnce(Return(Coords{ {0, 1}, {1, 0} }));

	auto board = life::Create({ {{""}, Coords{{1, 2}}}, {{""}, Coords{{6, 3}}} }, generator);

	EXPECT_EQ(7, board.width());
	EXPECT_EQ(5, board.height());
}

TEST_F(BoardCreation, create_with_multiple_patterns_and_offsets_sets_cells_correctly)
{
	auto dataset = std::vector<Coord>{ {0, 0}, {6, 1}, {5, 2}, {3, 4} };

	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {0, 0}, {3, 4} }))
		.WillOnce(Return(Coords{ {0, 1}, {1, 0} }));

	auto board = life::Create({ {{""}, Coords{{1, 2}}}, {{""}, Coords{{6, 3}}} }, generator);

	for (size_t j=0; j<5; ++j) {
		for (size_t i=0; i<7; ++i) {
			bool isAlive = std::find(dataset.begin(), dataset.end(), Coord{i, j}) != dataset.end();
			EXPECT_EQ(isAlive, board.isAlive({i, j}));
		}
	}
}

TEST_F(BoardCreation, create_with_one_pattern_with_multiple_offsets)
{
	auto dataset = std::vector<Coord>{ {0, 1}, {1, 0}, {5, 3}, {6, 2} };

	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {0, 1}, {1, 0} }));

	auto board = life::Create({ {{""}, Coords{ {0, 0}, {5, 2} }} }, generator);

	for (size_t j=0; j<4; ++j) {
		for (size_t i=0; i<7; ++i) {
			bool isAlive = std::find(dataset.begin(), dataset.end(), Coord{i, j}) != dataset.end();
			EXPECT_EQ(isAlive, board.isAlive({i, j}));
		}
	}
}
