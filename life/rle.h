#pragma once

#include "board.h"
#include <string>
#include <vector>
#include <memory>

namespace life {

struct Offset {
	const unsigned int x;
	const unsigned int y;
};

struct Input {
	const std::string pattern;
	const Offset offset;
};

std::vector<Coord> FromRLE(const std::string& pattern);

//std::unique_ptr<Board> Create(Input);

} // end namespace
