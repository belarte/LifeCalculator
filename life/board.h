#pragma once

#include <string>

namespace life {

class Board
{
public:
	Board(int w, int h) :
		m_width{w},
		m_height{h}
	{
	}

	int width() const
	{
		return m_width;
	}

	int height() const
	{
		return m_height;
	}

private:
	int m_width;
	int m_height;
};

class RLEParser
{
public:
	Board parse(const std::string& input) const
	{
		return Board{int(input[4] - '0'), int(input[11] - '0')};
	}
};

Board FromRLE(const std::string& pattern)
{
	RLEParser parser;
	return parser.parse(pattern);
}

} // end namespace
