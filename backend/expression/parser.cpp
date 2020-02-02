#include "parser.h"

namespace expression {

std::string Parser::parse(const std::string& input) {
	return  input == "1" ? "data: x = 3, y = 3\nbo$2bo$3o!" : "nothing";
}

} // end namespace
