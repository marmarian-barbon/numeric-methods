#include "stdafx.h"
#include "DifferencedSolutions.hpp"

namespace NumericMethods
{
	DifferencedSolutions::DifferencedSolutions(
		Domain&& exactSolution,
		std::map<std::wstring, DifferencedSolution>&& taggedDifferencedSolutions) :
		ExactSolution(exactSolution),
		TaggedDifferencedSolutions(taggedDifferencedSolutions)
	{ }
}
