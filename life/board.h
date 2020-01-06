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

Board FromRLE(const std::string& pattern)
{
	return Board{int(pattern[4] - '0'), int(pattern[11] - '0')};
}

} // end namespace
