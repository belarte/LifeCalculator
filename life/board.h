#pragma once

#include <cstdint>
#include <vector>

namespace life {

struct Coord
{
	unsigned int x;
	unsigned int y;
};

class Board
{
public:
	Board(int w, int h) :
		m_width{w},
		m_height{h},
		m_cells((m_width+2) * (m_height+2), 0)
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

	bool isAlive(Coord c) const
	{
		return m_cells[index(c)] > 0;
	}

	void setAlive(Coord c)
	{
		m_cells[index(c)] = 1;
	}

private:
	int index(Coord c) const
	{
		return (c.y + 1) * (m_width + 2) + c.x + 1;
	}

	int m_width;
	int m_height;
	std::vector<uint8_t> m_cells;
};

} // end namespace
