#include <boost/beast/websocket.hpp>

using namespace boost::beast::websocket;

int main(int, char**)
{
	try {
		auto const address = boost::asio::ip::make_address("127.0.0.1");
		auto const port = static_cast<unsigned short>(8970);

		boost::asio::io_context ioc{1};
		boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};
		boost::asio::ip::tcp::socket socket{ioc};

		acceptor.accept(socket);
		boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{std::move(socket)};
		ws.accept();

		boost::beast::multi_buffer buffer;
		ws.read(buffer);
		ws.text(ws.got_text());
		ws.write(boost::asio::buffer("ctrl: shutdown"));
		ws.close(boost::beast::websocket::close_code::normal);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
