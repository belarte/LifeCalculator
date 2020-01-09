#pragma once

#include "board.h"
#include <string>
#include <vector>

namespace life {

std::vector<Coord> FromRLE(const std::string& pattern);

} // end namespace
