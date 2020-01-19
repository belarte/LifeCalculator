#pragma once

#include <vector>

namespace life {

struct Coord
{
	unsigned int x;
	unsigned int y;
};

bool operator==(const Coord& left, const Coord& right);

Coord operator+(Coord left, Coord right);
Coord operator-(Coord left, Coord right);

using Coords = std::vector<Coord>;

} // end namespace
