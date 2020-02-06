#include "rle.h"
#include "board.h"
#include "utils/parser.h"

#include <sstream>
#include <stdexcept>

namespace life {

namespace {

class RLEParser
{
public:
	RLEParser(const std::string& input) :
		m_parser{input}
	{}

	Coords parse()
	{
		parseHeader();
		unsigned int line = 0;
		while (!m_parser.readChar('!')) {
			readLine(line);
			++line;
		}
		return std::move(m_output);
	}

private:
	void parseHeader()
	{
		if (!m_parser.readString("x = ") || !m_parser.readInt()) {
			throw std::runtime_error("Header incorrect, cannot read width");
		}

		if (!m_parser.readString(", y = ") || !m_parser.readInt()) {
			throw std::runtime_error("Header incorrect, cannot read height");
		}

		while (!m_parser.readChar('\n')) {
			// Skipping to end of the line
		}
	}

	bool readLine(unsigned int line)
	{
		unsigned int column = 0;

		while (!m_parser.readChar('$')) {
			unsigned int n = m_parser.readInt() ? m_parser.lastInt() : 1;

			if (m_parser.readChar('o')) {
				for (unsigned int i=column; i<column+n; ++i) {
					m_output.push_back({i, line});
				}
			} else if (!m_parser.readChar('b')) {
				return false;
			}

			column += n;
		}

		return true;
	}

	utils::Parser m_parser;
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
