#include <string>

namespace utils {

class Parser {
public:
	Parser(const std::string& input);

	void skipWhitespaces();

	bool readInt();
	uint32_t lastInt() const;

	bool readChar(char c);
	bool readString(const std::string& s);

private:
	bool isDigit() const;
	bool isWhitespace() const;

	unsigned int m_index;
	int m_lastInt;
	const std::string m_input;
};

} // end namespace
