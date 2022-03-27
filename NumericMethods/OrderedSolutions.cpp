#include "stdafx.h"
#include "OrderedSolutions.hpp"

namespace NumericMethods
{
	OrderedSolutions::OrderedSolutions(
		DifferencedSolutions&& differencedSolutions,
		std::map<size_t, Domain>&& exactOrderedSolutions,
		std::map<std::wstring, std::map<size_t, OrderedSolution>>&& taggedOrderedSolutions) :
		DifferencedSolutions(differencedSolutions),
		ExactOrderedSolutions(exactOrderedSolutions),
		TaggedOrderedSolutions(taggedOrderedSolutions)
	{ }

	OrderedSolutions::OrderedSolutions(
		Domain&& firstOrderExactSolution,
		std::map<std::wstring, DifferencedSolution>&& firstOrderTaggedSolutions,
		std::map<size_t, Domain>&& exactOrderedSolutions,
		std::map<std::wstring, std::map<size_t, OrderedSolution>>&& taggedOrderedSolutions) :
		DifferencedSolutions(std::move(firstOrderExactSolution), std::move(firstOrderTaggedSolutions)),
		ExactOrderedSolutions(exactOrderedSolutions),
		TaggedOrderedSolutions(taggedOrderedSolutions)
	{ }
}

