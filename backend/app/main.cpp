#include "websocket/websocket.h"

int main(int, char**)
{
	try {
		std::map<std::string, std::string> communications{
			{"expr=0", "nothing"},
			{"expr=1", "data: x = 3, y = 3\nbo$2bo$3o!"}
		};

		ws::Websocket ws{communications};
		ws.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
