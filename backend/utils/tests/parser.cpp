#include "../parser.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace utils;
using namespace testing;

TEST(ParserCan, read_integer_if_at_correct_position)
{
	Parser parser{"1234"};

	EXPECT_TRUE(parser.readInt());
	EXPECT_THAT(parser.lastInt(), 1234);
}

TEST(ParserCan, read_integer_when_prefixed_by_zeros)
{
	Parser parser{"00998877"};

	EXPECT_TRUE(parser.readInt());
	EXPECT_THAT(parser.lastInt(), 998877);
}

TEST(ParserCannot, read_integer_if_on_whitespaces)
{
	Parser parser{" 1234"};

	EXPECT_FALSE(parser.readInt());
}

TEST(ParserCan, read_integer_after_skipping_whitespaces)
{
	Parser parser{" \n \t 3456"};
	parser.skipWhitespaces();

	EXPECT_TRUE(parser.readInt());
	EXPECT_THAT(parser.lastInt(), 3456);
}

TEST(ParserCan, read_integer_when_other_characters_after)
{
	Parser parser{"987other stuff"};

	EXPECT_TRUE(parser.readInt());
	EXPECT_THAT(parser.lastInt(), 987);
}

TEST(ParserCan, read_consecutive_chars)
{
	Parser parser{"string"};

	for (const auto c : "string") {
		EXPECT_TRUE(parser.readChar(c));
	}
}

TEST(ParserCannot, read_incorrect_char)
{
	Parser parser{"string"};

	EXPECT_FALSE(parser.readChar('t'));
}

TEST(ParserCan, read_string)
{
	Parser parser{"some content"};

	EXPECT_TRUE(parser.readString("some"));
	parser.skipWhitespaces();
	EXPECT_TRUE(parser.readString("content"));
}

TEST(ParserCannot, read_erroneous_string)
{
	Parser parser{"string"};

	EXPECT_FALSE(parser.readString("strung"));
}

TEST(ParserCan, read_string_after_failing_to_read_string)
{
	Parser parser{"string"};

	parser.readString("strung");
	EXPECT_TRUE(parser.readString("string"));
}
