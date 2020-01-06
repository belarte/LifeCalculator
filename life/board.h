#pragma once

#include <memory>
#include <string>

namespace life {

class Board
{
public:
	Board(int w, int h) :
		m_width{w},
		m_height{h}
	{
	}

	int width() const
	{
		return m_width;
	}

	int height() const
	{
		return m_height;
	}

private:
	int m_width;
	int m_height;
};

class RLEParser
{
public:
	RLEParser(const std::string& input) :
		m_index{0},
		m_lastInt{0},
		m_input(input)
	{}

	std::unique_ptr<Board> parse() {
		parseHeader();
		return std::move(m_output);
	}

private:
	void parseHeader()
	{
		if (!readString("x = ") || !readInt()) {
			throw std::runtime_error("Header incorrect, cannot read width");
		}
		int width = m_lastInt;

		if (!readString(", y = ") || !readInt()) {
			throw std::runtime_error("Header incorrect, cannot read height");
		}
		int height = m_lastInt;

		m_output = std::make_unique<Board>(width, height);

		if (!readString("\n")) {
			throw std::runtime_error("Header incorrect, missing new line");
		}
	}

	bool readString(const std::string& s) {
		for (unsigned int i=0; i<s.size(); ++i) {
			if (s[i] != m_input[m_index]) {
				return false;
			}

			++m_index;
		}

		return true;
	}

	bool readInt() {
		m_lastInt = 0;
		unsigned int start = m_index;

		while (isDigit()) {
			m_lastInt *= 10;
			m_lastInt += m_input[m_index] - '0';
			++m_index;
		}

		return m_index != start;
	}

	bool isDigit() const {
		return m_input[m_index] >= '0' && m_input[m_index] <= '9';
	}

	unsigned int m_index;
	int m_lastInt;
	const std::string m_input;
	std::unique_ptr<Board> m_output;
};

std::unique_ptr<Board> FromRLE(const std::string& pattern)
{
	RLEParser parser(pattern);
	return parser.parse();
}

} // end namespace
