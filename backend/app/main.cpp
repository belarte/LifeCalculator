#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/websocket.hpp>

using namespace boost::beast::websocket;

class Websocket
{
public:
	Websocket() {
		const boost::asio::ip::address address = boost::asio::ip::make_address("127.0.0.1");
		const unsigned short port = 8970;
		boost::asio::io_context ioc{1};
		boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};
		boost::asio::ip::tcp::socket socket{ioc};
		acceptor.accept(socket);
		m_websocket = std::make_unique<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>(std::move(socket));
		m_websocket->accept();
	}

	void run() {
		std::map<std::string, std::string> communications{
			{"ctrl: exit", "ctrl: shutdown"},
			{"app: expr=0", "app: nothing"},
			{"app: expr=1", "app: data: x = 3, y = 3\nbo$2bo$3o!"}
		};

		while(true) {
			boost::beast::multi_buffer buffer;
			m_websocket->read(buffer);
			std::string msg = boost::beast::buffers_to_string(buffer.data());

			auto check = communications.find(msg);
			if (check != communications.end()) {
				std::cout << "[recv] " << msg << std::endl;
				std::cout << "[send] " << check->second << std::endl;
				m_websocket->write(boost::asio::buffer(check->second));
			} else {
				m_websocket->write(boost::asio::buffer("ctrl: unknown message"));
				std::cout << "[send] " << "ctrl: unknown message" << std::endl;
			}

			if (msg == "ctrl: exit") {
				break;
			}
		}
	}

private:
	std::unique_ptr<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>> m_websocket;
};

int main(int, char**)
{
	try {
		Websocket ws;
		ws.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
