#pragma once

#include "types.h"

#include <string>

namespace life {

namespace rle {

// -o-
// --o
// ooo
const std::string Glider = R"(x = 3, y = 3
bo$2bo$3o!)";

// ---oo--oo
// o---o--oo
// oooo-----
// ---------
// oo-------
// oo-------
const std::string Eater = R"(x = 9, y = 6
3b2o2b2o$o3bo2b2o$4o$$2o$2o!)";

} // end namespace

class Board;

Coords FromRLE(const std::string& pattern);

std::string ToRLE(Board&);

} // end namespace
