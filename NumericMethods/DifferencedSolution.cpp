#include "stdafx.h"
#include "DifferencedSolution.hpp"

namespace NumericMethods
{
	DifferencedSolution::DifferencedSolution(Domain&& solution, double_t difference) :
		Solution(solution),
		Difference(difference)
	{ }
}
