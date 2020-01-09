#pragma once

#include <string>
#include <memory>

namespace life {

class Board;

struct Offset
{
	unsigned int x;
	unsigned int y;
};

struct Input {
	const std::string pattern;
	const Offset offset;
};

std::unique_ptr<Board> Create(Input);

} // end namespace
