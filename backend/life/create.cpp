#include "create.h"
#include "board.h"

#include <limits>

namespace life {

Board Create(Inputs inputs, Generator gen)
{
	size_t width = 0, height = 0;
	auto xOrigin = std::numeric_limits<size_t>::max();
	auto yOrigin = std::numeric_limits<size_t>::max();

	Coords coordinates;
	for (const auto input : inputs) {
		auto coords = gen(input.pattern);

		for (const auto offset : input.offsets) {
			for (const auto c : coords) {
				xOrigin = std::min(xOrigin, c.x + offset.x);
				yOrigin = std::min(yOrigin, c.y + offset.y);
				width = std::max(width, c.x + offset.x);
				height = std::max(height, c.y + offset.y);

				coordinates.push_back(c + Coord{offset.x, offset.y});
			}
		}
	}

	auto board = Board(width+1-xOrigin, height+1-yOrigin);
	for (const auto c : coordinates) {
		board.setAlive(c - Coord{xOrigin, yOrigin});
	}

	return board;
}

} // end namespace
