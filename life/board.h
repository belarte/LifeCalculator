#pragma once

#include "types.h"

#include <cstdint>
#include <vector>

namespace life {

class Board
{
public:
	Board(size_t w, size_t h) :
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
	size_t index(Coord c) const
	{
		return (c.y + 1) * (m_width + 2) + c.x + 1;
	}

	size_t m_width;
	size_t m_height;
	std::vector<uint8_t> m_cells;
};

} // end namespace
