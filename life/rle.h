#pragma once

#include <string>
#include <memory>

namespace life {

class Board;

std::unique_ptr<Board> FromRLE(const std::string& pattern);

} // end namespace
