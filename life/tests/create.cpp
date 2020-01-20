#include "../create.h"
#include "../board.h"
#include "../rle.h"

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
	MockGenerator mockGenerator;
	Generator generator = [&](const std::string& s){ return mockGenerator.create(s); };
};

TEST_F(BoardCreation, create_forwards_parameters_to_generator)
{
	EXPECT_CALL(mockGenerator, create("some input"));

	auto board = life::Create({ {{"some input"}, {}} }, generator);
}

TEST_F(BoardCreation, creates_with_dimension_from_pattern)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {0, 0}, {35, 8} }));

	auto board = life::Create({ {{""}, {}} }, generator);

	EXPECT_EQ(36, board->width());
	EXPECT_EQ(9, board->height());
}

TEST_F(BoardCreation, create_trims_size_when_pattern_does_not_start_at_origin)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {3, 4} }));

	auto board = life::Create({ {{""}, {}} }, generator);

	EXPECT_EQ(1, board->width());
	EXPECT_EQ(1, board->height());
}

TEST_F(BoardCreation, create_trims_size_when_pattern_is_offset)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {0, 0}, {3, 4} }));

	auto board = life::Create({ {{""}, {1, 2}} }, generator);

	EXPECT_EQ(4, board->width());
	EXPECT_EQ(5, board->height());
}

TEST_F(BoardCreation, create_with_pattern)
{
	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} }));

	auto board = life::Create({ {{""}, {}} }, generator);

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

TEST_F(BoardCreation, create_with_multiple_patterns_and_offsets_return_board_with_correct_size)
{
	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {0, 0}, {3, 4} }))
		.WillOnce(Return(Coords{ {0, 1}, {1, 0} }));

	auto board = life::Create({ {{""}, {1, 2}}, {{""}, {6, 3}} }, generator);

	EXPECT_EQ(7, board->width());
	EXPECT_EQ(5, board->height());
}

TEST_F(BoardCreation, create_with_multiple_patterns_and_offsets_sets_cells_correctly)
{
	auto dataset = std::vector<Coord>{ {0, 0}, {6, 1}, {5, 2}, {3, 4} };

	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {0, 0}, {3, 4} }))
		.WillOnce(Return(Coords{ {0, 1}, {1, 0} }));

	auto board = life::Create({ {{""}, {1, 2}}, {{""}, {6, 3}} }, generator);

	for (size_t j=0; j<5; ++j) {
		for (size_t i=0; i<7; ++i) {
			bool isAlive = std::find(dataset.begin(), dataset.end(), Coord{i, j}) != dataset.end();
			EXPECT_EQ(isAlive, board->isAlive({i, j}));
		}
	}
}
