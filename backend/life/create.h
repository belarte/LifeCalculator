#pragma once

#include "types.h"

#include <string>
#include <memory>
#include <functional>

namespace life {

class Board;

using Generator = std::function<Coords(const std::string&)>;

Board Create(Inputs, Generator);

} // end namespace
