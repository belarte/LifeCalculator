#include "websocket.h"

#include <boost/beast/core/buffers_to_string.hpp>

#include <iostream>

namespace ws {

Websocket::Websocket(Communications comms) :
	m_appCommunications{comms},
	m_continue{true}
{
	const boost::asio::ip::address address = boost::asio::ip::make_address("127.0.0.1");
	const unsigned short port = 8970;
	boost::asio::io_context ioc{1};
	boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};
	boost::asio::ip::tcp::socket socket{ioc};
	acceptor.accept(socket);
	m_websocket = std::make_unique<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>(std::move(socket));
	m_websocket->accept();
}

void Websocket::run() {
	while(m_continue) {
		boost::beast::multi_buffer buffer;
		m_websocket->read(buffer);
		std::string msg = boost::beast::buffers_to_string(buffer.data());
		std::cout << "[recv] " << msg << std::endl;

		std::string reply;
		if (msg == "ctrl: exit") {
			reply = "ctrl: shutdown";
			m_continue = false;
		} else if (msg.rfind("app: ", 0) == 0) {
			reply = processAppMessages( { msg.begin()+5, msg.end() } );
		} else {
			reply = "ctrl: unknown message";
		}

		std::cout << "[send] " << reply << std::endl;
		m_websocket->write(boost::asio::buffer(reply));
	}
}

const std::string Websocket::processAppMessages(const std::string& msg) {
	for (const auto& comm : m_appCommunications) {
		if (msg.rfind(comm.first, 0) == 0) {
			std::string content{ msg.begin() + comm.first.size(), msg.end() };
			return std::string{"app: "}.append(comm.second(content));
		}
	}

	return "";
}

} // end namespace
