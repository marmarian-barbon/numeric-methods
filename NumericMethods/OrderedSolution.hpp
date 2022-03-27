#pragma once
#include "stdafx.h"

#include "DifferencedSolution.hpp"

namespace NumericMethods
{
	struct OrderedSolution : public DifferencedSolution
	{
	public:
		double_t Order;

	public:
		OrderedSolution(DifferencedSolution&& differencedSolution, double_t order);

		OrderedSolution(Domain&& solution, double_t difference, double_t order);
	};
}

