#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "BaseSolver.hpp"
#include "DifferencedSolutions.hpp"
#include "OrderedSolutions.hpp"

namespace NumericMethods
{
	class SolutionComparer
	{
	public:
		SolutionComparer() = delete;

	public:
		static DifferencedSolutions MeterSolversDifferences(
			double_t begin,
			double_t end,
			size_t count,
			const std::map<std::wstring, std::unique_ptr<BaseSolver>>& taggedSolvers,
			const std::function<double_t(double_t)>& fieldFunction,
			const std::function<double_t(double_t)>& exactSolutionFunction
		);

		static OrderedSolutions MeterSolversOrders(
			double_t begin,
			double_t end,
			size_t baseCount,
			const std::map<std::wstring, std::unique_ptr<BaseSolver>>& taggedSolvers,
			const std::function<double_t(double_t)>& fieldFunction,
			const std::function<double_t(double_t)>& exactSolutionFunction,
			const std::vector<size_t>& countMultipliers
		);

	private:
		static double_t MeterSolutionsDifference(const Domain& exactSolution, const Domain& calculatedSolution);

		static double_t MeterAccuracyOrder(double_t coarseDifference, double_t accurateDifference, double_t multiplier);
	};
}
