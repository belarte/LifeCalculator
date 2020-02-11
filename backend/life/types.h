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

struct Input {
	std::string pattern;
	Coords offsets;
};

bool operator==(const Input& left, const Input& right);

std::ostream& operator<<(std::ostream&, const Input&);

using Inputs = std::vector<Input>;

} // end namespace
