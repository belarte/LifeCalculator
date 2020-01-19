#include "create.h"
#include "rle.h"
#include "board.h"
#include <limits>

namespace life {

std::unique_ptr<Board> Create(Input input, Generator gen)
{
	auto coords = gen(input.pattern);
	auto xOffset = input.offset.x;
	auto yOffset = input.offset.y;

	unsigned int width = 0, height = 0;
	unsigned int xOrigin = std::numeric_limits<unsigned int>::max();
	unsigned int yOrigin = std::numeric_limits<unsigned int>::max();
	for (const auto c : coords) {
		xOrigin = std::min(xOrigin, c.x + xOffset);
		yOrigin = std::min(yOrigin, c.y + yOffset);
		width = std::max(width, c.x + xOffset);
		height = std::max(height, c.y + yOffset);
	}

	auto board = std::make_unique<Board>(width+1-xOrigin, height+1-yOrigin);
	for (const auto c : coords) {
		board->setAlive(c);
	}

	return board;
}

} // end namespace
