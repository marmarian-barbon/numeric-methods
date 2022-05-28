#include "stdafx.h"
#include "SolutionComparer.hpp"

namespace NumericMethods
{
	std::map<std::wstring, double_t> SolutionComparer::MeterSolversDifferences(
		const std::set<std::wstring>& tags,
		const Domain<double_t>& domain,
		const std::function<ValueType(double_t widthCoordinate, double_t heightCoordinate)>& exactSolutionFunction,
		const std::map<std::wstring, std::unique_ptr<Domain<ValueType>>>& taggedSolutions)
	{
		auto exactSolution = Domain<ValueType>(
			Dimension(domain.Height.Begin, domain.Height.End, domain.Height.Count - 1, true),
			Dimension(domain.Width.Begin, domain.Width.End, domain.Width.Count - 1, true),
			exactSolutionFunction
		);

		auto result = std::map<std::wstring, double_t>();
		for (const auto& tag : tags)
		{
			auto difference = MeterSolutionsDifference(exactSolution, *(taggedSolutions.at(tag).get()));
			result.emplace(tag, difference);
		}

		return result;
	}

	std::map<std::wstring, double_t> SolutionComparer::MeterSolutionOrders(
		const std::set<std::wstring>& tags,
		const std::map<std::wstring, double_t>& coarseDifferences,
		const std::map<std::wstring, double_t>& accurateDifferences,
		size_t multiplier)
	{
		auto result = std::map<std::wstring, double_t>();
		for (const auto& tag : tags)
		{
			auto order = MeterAccuracyOrder(coarseDifferences.at(tag), accurateDifferences.at(tag), double_t(multiplier));
			result.emplace(tag, order);
		}

		return result;
	}

	double_t SolutionComparer::MeterSolutionsDifference(const Domain<ValueType>& exactSolution, const Domain<ValueType>& calculatedSolution)
	{
		auto calculateLength = [](const ValueType& exact, const ValueType& calculated) {
			return std::sqrt(std::abs(std::pow(exact[0] - calculated[0], 2)) + std::abs(std::pow(exact[1] - calculated[1], 2)));
		};

		auto max = 0.;
		for (size_t i = 0; i < exactSolution.Height.Count; ++i)
		{
			for (size_t j = 0; j < exactSolution.Width.Count; ++j)
			{
				max = std::max(max, calculateLength(exactSolution.Values[i][j], calculatedSolution.Values[i][j]));
			}
		}

		return max;
	}

	double_t SolutionComparer::MeterAccuracyOrder(double_t coarseDifference, double_t accurateDifference, double_t multiplier)
	{
		return std::log(coarseDifference / accurateDifference) / std::log(multiplier);
	}
}
