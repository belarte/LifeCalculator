#pragma once

#include "life/types.h"
#include <algorithm>

namespace expression {

class Bit
{
public:
	Bit(const life::Inputs& data, uint32_t width);
	Bit(const Bit& left, const Bit& right);

	bool operator==(const Bit& other) const;

	life::Inputs output() const;
	void offset(life::Coord);
	uint32_t width() const;

private:
	life::Inputs m_data;
	uint32_t m_width;
};

} // end namespace
