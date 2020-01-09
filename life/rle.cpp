#include "rle.h"
#include "board.h"
#include <stdexcept>

namespace life {

namespace {

class RLEParser
{
public:
	RLEParser(const std::string& input) :
		m_index{0},
		m_lastInt{0},
		m_input(input)
	{}

	std::vector<Coord> parse()
	{
		parseHeader();
		unsigned int line = 0;
		while (!readChar('!')) {
			readLine(line);
			++line;
		}
		return std::move(m_output);
	}

private:
	void parseHeader()
	{
		if (!readString("x = ") || !readInt()) {
			throw std::runtime_error("Header incorrect, cannot read width");
		}

		if (!readString(", y = ") || !readInt()) {
			throw std::runtime_error("Header incorrect, cannot read height");
		}

		if (!readString("\n")) {
			throw std::runtime_error("Header incorrect, missing new line");
		}
	}

	bool readLine(unsigned int line)
	{
		unsigned int column = 0;

		while (!readChar('$')) {
			unsigned int n = readInt() ? m_lastInt : 1;

			if (readChar('o')) {
				for (unsigned int i=column; i<column+n; ++i) {
					m_output.push_back({i, line});
				}
			} else if (!readChar('b')) {
				return false;
			}

			column += n;
		}

		return true;
	}

	bool readString(const std::string& s)
	{
		for (char c : s) {
			if (!readChar(c)) {
				return false;
			}
		}

		return true;
	}

	bool readChar(char c)
	{
		if (m_input[m_index] == c) {
			++m_index;
			return true;
		}

		return false;
	}

	bool readInt()
	{
		m_lastInt = 0;
		unsigned int start = m_index;

		while (isDigit()) {
			m_lastInt *= 10;
			m_lastInt += m_input[m_index] - '0';
			++m_index;
		}

		return m_index != start;
	}

	bool isDigit() const
	{
		return m_input[m_index] >= '0' && m_input[m_index] <= '9';
	}

	unsigned int m_index;
	int m_lastInt;
	const std::string m_input;
	std::vector<Coord> m_output;
};

} // end namespace

std::vector<Coord> FromRLE(const std::string& pattern)
{
	RLEParser parser(pattern);
	return parser.parse();
}

} // end namespace
