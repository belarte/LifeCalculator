#pragma once

#include "board.h"
#include "types.h"
#include <string>

namespace life {

Coords FromRLE(const std::string& pattern);

} // end namespace
