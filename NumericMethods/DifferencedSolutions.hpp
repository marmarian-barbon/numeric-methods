#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "DifferencedSolution.hpp"

namespace NumericMethods
{
	struct DifferencedSolutions
	{
	public:
		Domain ExactSolution;

		std::map<std::wstring, DifferencedSolution> TaggedDifferencedSolutions;

	public:
		DifferencedSolutions(
			Domain&& exactSolution,
			std::map<std::wstring, DifferencedSolution>&& taggedDifferencedSolutions
		);
	};
}
