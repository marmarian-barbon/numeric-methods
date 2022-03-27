#pragma once
#include "stdafx.h"

#include "Domain.hpp"

namespace NumericMethods
{
	struct DifferencedSolution
	{
	public:
		Domain Solution;

		double_t Difference;

	public:
		DifferencedSolution(Domain&& solution, double_t difference);
	};
}
