#include "types.h"
#include <algorithm>

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

bool operator==(const Input& left, const Input& right)
{
	return left.pattern == right.pattern &&
		std::is_permutation(left.offsets.begin(), left.offsets.end(), right.offsets.begin());
}

std::ostream& operator<<(std::ostream& oss, const Input& input)
{
	oss << input.pattern << " ";
	for ( const auto& c : input.offsets) {
		oss << c << " ";
	}
	return oss;
}

} //end namespace
