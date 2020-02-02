#include "expression/parser.h"
#include "websocket/websocket.h"

int main(int, char**)
{
	try {
		ws::Websocket::Communications communications{
			{ "expr=", [](const std::string& s) { return expression::Parser{}.parse(s); } },
		};

		ws::Websocket ws{communications};
		ws.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
