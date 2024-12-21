


#ifndef ENGINE_MATH_CPP
#define ENGINE_MATH_CPP

#include "CONFIG.hpp"
#include "MATH.hpp"

namespace ENGINE_MATH {
	int get_positive(int number)
	{
		if (number >= 0)
		{
			return number;
		}
		return -number;
	}
	float get_positive(float number)
	{
		if (number >= 0)
		{
			return number;
		}
		return -number;
	}
}

#endif // ENGINE_MATH_CPP