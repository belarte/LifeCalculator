#pragma once

#include "types.h"

#include <string>
#include <memory>
#include <functional>

namespace life {

class Board;

struct Input {
	const std::string pattern;
	const Coords offsets;
};

using Inputs = std::vector<Input>;

using Generator = std::function<Coords(const std::string&)>;

Board Create(Inputs, Generator);

} // end namespace
