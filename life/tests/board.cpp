#include "../board.h"
#include "gtest/gtest.h"

TEST(BoardCreation, creates_with_correct_dimensions)
{
	auto board = life::FromRLE("x = 15, y = 6\n");

	ASSERT_EQ(15, board->width());
	ASSERT_EQ(6, board->height());
}
