#include "create.h"
#include "rle.h"
#include "board.h"

namespace life {

std::unique_ptr<Board> Create(Input input)
{
	auto coords = FromRLE(input.pattern);

	unsigned int width = 0, length = 0;
	for (const auto c : coords) {
		width = std::max(width, c.x);
		length = std::max(length, c.y);
	}

	auto board = std::make_unique<Board>(width+1, length+1);
	for (const auto c : coords) {
		board->setAlive(c);
	}

	return std::move(board);
}

} // end namespace
