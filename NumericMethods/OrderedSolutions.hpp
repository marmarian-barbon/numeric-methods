#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "OrderedSolution.hpp"
#include "DifferencedSolutions.hpp"

namespace NumericMethods
{
	struct OrderedSolutions : DifferencedSolutions
	{
	public:
		std::map<size_t, Domain> ExactOrderedSolutions;

		std::map<std::wstring, std::map<size_t, OrderedSolution>> TaggedOrderedSolutions;

	public:
		OrderedSolutions(
			DifferencedSolutions&& differencedSolutions,
			std::map<size_t, Domain>&& exactOrderedSolutions,
			std::map<std::wstring, std::map<size_t, OrderedSolution>>&& taggedOrderedSolutions
		);

		OrderedSolutions(
			Domain&& firstOrderExactSolution,
			std::map<std::wstring, DifferencedSolution>&& firstOrderTaggedSolutions,
			std::map<size_t, Domain>&& exactOrderedSolutions,
			std::map<std::wstring, std::map<size_t, OrderedSolution>>&& taggedOrderedSolutions
		);
	};
}
