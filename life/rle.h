#pragma once

#include <string>
#include <memory>

namespace life {

class Board;

struct Offset {
	const unsigned int x;
	const unsigned int y;
};

struct Input {
	const std::string pattern;
	const Offset offset;
};

std::unique_ptr<Board> FromRLE(Input);

} // end namespace
