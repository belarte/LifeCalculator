#pragma once

#include <vector>

namespace life {

struct Coord
{
	unsigned int x;
	unsigned int y;
};

using Coords = std::vector<Coord>;

} // end namespace
