#include "bit.h"

namespace expression {

Bit::Bit(const life::Inputs& data) :
	m_data{data}
{}

Bit::Bit(const Bit& left, const Bit& right)
{
	m_data = left.m_data;
	for (const auto& input : right.m_data) {
		auto it = std::find_if(m_data.begin(), m_data.end(), [input](const life::Input& i) {
			return input.pattern == i.pattern;
		});
		if (it == m_data.end()) {
			m_data.push_back(input);
		} else {
			it->offsets.insert(it->offsets.end(), input.offsets.begin(), input.offsets.end());
		}
	}
}

bool Bit::operator==(const Bit& other) const
{
	return m_data == other.m_data;
}

life::Inputs Bit::output() const
{
	return m_data;
}
} // end namespace
