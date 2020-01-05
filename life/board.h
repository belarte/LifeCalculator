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

	static Board Create(const std::string& pattern)
	{
		return Board{int(pattern[4] - '0'), int(pattern[11] - '0')};
	}

private:
	int m_width;
	int m_height;
};

} // end namespace
