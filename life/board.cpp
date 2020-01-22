#include "board.h"

namespace life {

Board::Board(size_t w, size_t h) :
	m_width{w},
	m_height{h},
	m_currentLayer{0},
	m_cells(2, std::vector<uint8_t>((m_width+2) * (m_height+2), 0))
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
	return m_cells[m_currentLayer].at(index(c)) > 0;
}

void Board::setAlive(Coord c)
{
	m_cells[m_currentLayer].at(index(c)) = 1;
}

void Board::simulate()
{
	for (size_t j=0; j<m_height; ++j) {
		for (size_t i=0; i<m_width; ++i) {
			Coord c{i, j};
			auto count = countAliveNeighbours(c);

			if (isAlive(c)) {
				if (count == 2 || count == 3) {
					m_cells[nextLayer()].at(index(c)) = 1;
				}
			} else {
				if (count == 3) {
					m_cells[nextLayer()].at(index(c)) = 1;
				}
			}
		}
	}

	m_currentLayer = nextLayer();
}

size_t Board::countAliveNeighbours(Coord c) const
{
	size_t count = 0;
	count += isAlive({c.x - 1, c.y - 1}) ? 1 : 0;
	count += isAlive({c.x, c.y - 1})     ? 1 : 0;
	count += isAlive({c.x + 1, c.y - 1}) ? 1 : 0;
	count += isAlive({c.x - 1, c.y})     ? 1 : 0;
	count += isAlive({c.x + 1, c.y})     ? 1 : 0;
	count += isAlive({c.x - 1, c.y + 1}) ? 1 : 0;
	count += isAlive({c.x, c.y + 1})     ? 1 : 0;
	count += isAlive({c.x + 1, c.y + 1}) ? 1 : 0;
	return count;
}

size_t Board::index(Coord c) const
{
	return (c.y + 1) * (m_width + 2) + c.x + 1;
}

size_t Board::nextLayer() const
{
	return (m_currentLayer + 1) % 2;
}

} // end namespace
