#pragma once

#include <vector>

namespace life {

struct Coord
{
	size_t x;
	size_t y;
};

bool operator==(const Coord& left, const Coord& right);

Coord operator+(Coord left, Coord right);
Coord operator-(Coord left, Coord right);

using Coords = std::vector<Coord>;

} // end namespace
