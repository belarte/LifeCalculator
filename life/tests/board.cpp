#include "../create.h"
#include "../board.h"
#include "../rle.h"

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

	auto board = life::Create({{"some input"}, {}}, generator);
}

TEST_F(BoardCreation, creates_with_dimension_from_pattern)
{
	EXPECT_CALL(mockGenerator, create(_)).WillOnce(Return(Coords{ {35, 8} }));

	auto board = life::Create({}, generator);

	EXPECT_EQ(36, board->width());
	EXPECT_EQ(9, board->height());
}

TEST_F(BoardCreation, create_with_pattern)
{
	EXPECT_CALL(mockGenerator, create(_))
		.WillOnce(Return(Coords{ {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} }));

	auto board = life::Create({}, generator);

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
