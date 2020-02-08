#include "expression/parser.h"
#include "life/board.h"
#include "life/create.h"
#include "life/rle.h"
#include "websocket/websocket.h"

life::Board Create(const std::string& input)
{
	auto expr = expression::Parser{}.parse(input);
	return life::Create(expr->evaluate(), life::FromRLE);
}

int main(int, char**)
{
	try {
		ws::Websocket::Communications communications{
			{"expr=", [](const std::string& s) {
				auto board = Create(s);
				return ToRLE(board);
			}},
		};

		ws::Websocket ws{communications};
		ws.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
