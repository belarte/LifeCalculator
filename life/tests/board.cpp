#include "../board.h"
#include "gtest/gtest.h"

TEST(BoardCreation, creates_with_correct_dimensions)
{
	auto board = life::Board::Create("x = 5, y = 6");

	ASSERT_EQ(board.width(), 5);
	ASSERT_EQ(board.height(), 6);
}
