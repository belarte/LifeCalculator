#include "board.h"

namespace life {

Board::Board(size_t w, size_t h) :
	m_width{w},
	m_height{h},
	m_cells((m_width+2) * (m_height+2), 0)
{
}

int Board::width() const
{
	return m_width;
}

int Board::height() const
{
	return m_height;
}

bool Board::isAlive(Coord c) const
{
	return m_cells.at(index(c)) > 0;
}

void Board::setAlive(Coord c)
{
	m_cells.at(index(c)) = 1;
}

size_t Board::index(Coord c) const
{
	return (c.y + 1) * (m_width + 2) + c.x + 1;
}

} // end namespace
