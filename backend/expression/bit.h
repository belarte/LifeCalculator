#pragma once

#include "life/types.h"
#include <algorithm>

namespace expression {

class Bit
{
public:
	Bit(const life::Inputs& data);
	Bit(const Bit& left, const Bit& right);

	bool operator==(const Bit& other) const;

	life::Inputs output() const;

private:
	life::Inputs m_data;
};

} // end namespace
