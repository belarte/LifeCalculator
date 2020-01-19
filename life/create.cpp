#include "create.h"
#include "rle.h"
#include "board.h"
#include <limits>

namespace life {

std::unique_ptr<Board> Create(Input input, Generator gen)
{
	auto coords = gen(input.pattern);

	unsigned int width = 0, height = 0;
	unsigned int xOrigin = std::numeric_limits<unsigned int>::max();
	unsigned int yOrigin = std::numeric_limits<unsigned int>::max();
	for (const auto c : coords) {
		xOrigin = std::min(xOrigin, c.x);
		yOrigin = std::min(yOrigin, c.y);
		width = std::max(width, c.x);
		height = std::max(height, c.y);
	}

	auto board = std::make_unique<Board>(width+1-xOrigin, height+1-yOrigin);
	for (const auto c : coords) {
		board->setAlive(c);
	}

	return board;
}

} // end namespace
