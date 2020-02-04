#include "expression/parser.h"
#include "websocket/websocket.h"

std::string Create(const std::string& input)
{
	auto expr = expression::Parser{}.parse(input);
	return expr->evaluate();
}

int main(int, char**)
{
	try {
		ws::Websocket::Communications communications{
			{ "expr=", [](const std::string& s) { return Create(s); } },
		};

		ws::Websocket ws{communications};
		ws.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
