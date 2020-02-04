#include "rle.h"

#include "board.h"

#include <sstream>
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

	Coords parse()
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

		while (!readChar('\n')) {
			// Skipping to end of the line
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
	Coords m_output;
};

} // end namespace

Coords FromRLE(const std::string& pattern)
{
	RLEParser parser(pattern);
	return parser.parse();
}


std::string ToRLE(Board& board)
{
	if (board.height() > 0 && board.width() > 0) {
		std::ostringstream oss;
		oss << "x = " << board.width() << ", y = " << board.height() << "\n";
		for (size_t j=0; j<board.height(); ++j) {
			std::string line;
			for (size_t i=0; i<board.width(); ++i) {
				line += board.isAlive({i, j}) ? 'o' : 'b';
			}

			while (line.back() == 'b') {
				line.pop_back();
			}

			if (line.empty()) {
				oss << "$";
				continue;
			}

			char current = line.front();
			int count = 1;

			for (size_t i=1; i<line.size(); ++i) {
				char c = line[i];
				if (current == c) {
					++count;
				} else {
					if (count > 1) {
						oss << count;
					}
					oss << current;
					current = c;
					count = 1;
				}
			}
			if (count > 1) {
				oss << count;
			}
			oss << current << (j == board.height()-1 ? '!' : '$');
		}
		return oss.str();
	}

	return "nothing";
}

} // end namespace
