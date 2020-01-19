#include "create.h"
#include "board.h"

#include <limits>

namespace life {

std::unique_ptr<Board> Create(Inputs inputs, Generator gen)
{
	unsigned int width = 0, height = 0;
	unsigned int xOrigin = std::numeric_limits<unsigned int>::max();
	unsigned int yOrigin = std::numeric_limits<unsigned int>::max();

	Coords coordinates;
	for (const auto input : inputs) {
		auto coords = gen(input.pattern);
		auto xOffset = input.offset.x;
		auto yOffset = input.offset.y;

		for (const auto c : coords) {
			xOrigin = std::min(xOrigin, c.x + xOffset);
			yOrigin = std::min(yOrigin, c.y + yOffset);
			width = std::max(width, c.x + xOffset);
			height = std::max(height, c.y + yOffset);

			coordinates.push_back(c + Coord{xOffset, yOffset});
		}
	}

	auto board = std::make_unique<Board>(width+1-xOrigin, height+1-yOrigin);
	for (const auto c : coordinates) {
		board->setAlive(c - Coord{xOrigin, yOrigin});
	}

	return board;
}

} // end namespace
