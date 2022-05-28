#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "BaseSolver.hpp"
#include "Types.h"

namespace NumericMethods
{
	class SolutionComparer
	{
	public:
		SolutionComparer() = delete;

	public:
		static std::map<std::wstring, double_t> MeterSolversDifferences(
			const std::set<std::wstring>& tags,
			const Domain<double_t>& domain,
			const std::function<ValueType(double_t widthCoordinate, double_t heightCoordinate)>& exactSolutionFunction,
			const std::map<std::wstring, std::unique_ptr<Domain<ValueType>>>& taggedSolutions
		);

		static std::map<std::wstring, double_t> MeterSolutionOrders(
			const std::set<std::wstring>& tags,
			const std::map<std::wstring, double_t>& coarseDifferences,
			const std::map<std::wstring, double_t>& accurateDifferences,
			size_t multiplier
		);

	private:
		static double_t MeterSolutionsDifference(const Domain<ValueType>& exactSolution, const Domain<ValueType>& calculatedSolution);

		static double_t MeterAccuracyOrder(double_t coarseDifference, double_t accurateDifference, double_t multiplier);
	};
}
