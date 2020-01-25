#pragma once

#include "types.h"

#include <string>

namespace life {

namespace rle {

const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

const std::string Eater = R"(x = 9, y = 6
3b2o2b2o$o3bo2b2o$4o$$2o$2o!)";

} // end namespace

Coords FromRLE(const std::string& pattern);

} // end namespace
