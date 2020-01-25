#pragma once

#include <ostream>
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

std::ostream& operator<<(std::ostream&, const Coord&);

using Coords = std::vector<Coord>;

} // end namespace
