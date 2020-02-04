#pragma once

#include "types.h"

#include <cstdint>
#include <vector>

namespace life {

class Board
{
public:
	Board(size_t w, size_t h);
	size_t width() const;
	size_t height() const;
	bool isAlive(Coord c) const;
	void setAlive(Coord c);

	void simulate();

private:
	size_t countAliveNeighbours(Coord) const;
	size_t index(Coord c) const;
	size_t nextLayer() const;

	size_t m_width;
	size_t m_height;
	size_t m_currentLayer;
	std::vector<std::vector<uint8_t>> m_cells;
};

} // end namespace
