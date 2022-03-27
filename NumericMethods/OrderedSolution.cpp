#include "stdafx.h"
#include "OrderedSolution.hpp"

namespace NumericMethods
{
	OrderedSolution::OrderedSolution(DifferencedSolution&& differencedSolution, double_t order) :
		DifferencedSolution(differencedSolution),
		Order(order)
	{ }

	OrderedSolution::OrderedSolution(Domain&& solution, double_t difference, double_t order) :
		DifferencedSolution(std::move(solution), difference),
		Order(order)
	{ }
}
