#include "types.h"

namespace life {

bool operator==(const Coord& left, const Coord& right)
{
	return left.x == right.x && left.y == right.y;
}

Coord operator+(Coord left, Coord right)
{
	return {left.x + right.x, left.y + right.y};
}

Coord operator-(Coord left, Coord right)
{
	return {left.x - right.x, left.y - right.y};
}

std::ostream& operator<<(std::ostream& oss, const Coord& c)
{
	oss << "(" << c.x << ", " << c.y << ")";
	return oss;
}

} //end namespace
