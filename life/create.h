#pragma once

#include "types.h"
#include <string>
#include <memory>

namespace life {

class Board;

struct Input {
	const std::string pattern;
	const Coord offset;
};

std::unique_ptr<Board> Create(Input);

} // end namespace
