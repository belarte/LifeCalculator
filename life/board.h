#pragma once

#include "types.h"

#include <cstdint>
#include <vector>

namespace life {

class Board
{
public:
	Board(size_t w, size_t h);
	int width() const;
	int height() const;
	bool isAlive(Coord c) const;
	void setAlive(Coord c);

private:
	size_t index(Coord c) const;

	size_t m_width;
	size_t m_height;
	std::vector<uint8_t> m_cells;
};

} // end namespace
