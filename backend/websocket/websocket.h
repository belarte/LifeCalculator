#include <boost/beast/websocket.hpp>

namespace ws {

class Websocket
{
public:
	Websocket(const std::map<std::string, std::string> comms);
	void run();

private:
	const std::string processAppMessages(const std::string& msg);

	std::unique_ptr<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>> m_websocket;
	std::map<std::string, std::string> m_appCommunications;
	bool m_continue;
};

} // end namespace
