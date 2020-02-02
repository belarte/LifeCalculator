#include <boost/beast/websocket.hpp>

namespace ws {

class Websocket
{
public:
	using Communication = std::function<std::string(const std::string&)>;
	using Communications = std::map<std::string, Communication>;

	Websocket(Communications);
	void run();

private:
	const std::string processAppMessages(const std::string& msg);

	std::unique_ptr<boost::beast::websocket::stream<boost::asio::ip::tcp::socket>> m_websocket;
	Communications m_appCommunications;
	bool m_continue;
};

} // end namespace
