#include "parser.h"

namespace utils {

Parser::Parser(const std::string& input) :
	m_index{0},
	m_lastInt{0},
	m_input(input)
{}

void Parser::skipWhitespaces()
{
	while (isWhitespace()) {
		++m_index;
	}
}

bool Parser::readInt()
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

uint32_t Parser::lastInt() const
{
	return m_lastInt;
}

bool Parser::readChar(char c)
{
	if (m_input[m_index] == c) {
		++m_index;
		return true;
	}

	return false;
}

bool Parser::readString(const std::string& s)
{
	uint32_t startIndex = m_index;

	for (char c : s) {
		if (!readChar(c)) {
			m_index = startIndex;
			return false;
		}
	}

	return true;
}

bool Parser::isDigit() const
{
	return m_input[m_index] >= '0' && m_input[m_index] <= '9';
}

bool Parser::isWhitespace() const
{
	std::string whitespaces = {' ', '\n', '\t'};
	return whitespaces.find(m_input[m_index]) != std::string::npos;
}

} // end namespace
