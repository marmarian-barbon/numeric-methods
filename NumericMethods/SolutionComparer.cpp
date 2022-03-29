#include "stdafx.h"
#include "SolutionComparer.hpp"

namespace NumericMethods
{
	DifferencedSolutions SolutionComparer::MeterSolversDifferences(
		double_t begin,
		double_t end,
		size_t count,
		const std::map<std::wstring, std::unique_ptr<BaseSolver>>& taggedSolvers,
		const std::function<double_t(double_t)>& fieldFunction,
		const std::function<double_t(double_t)>& exactSolutionFunction)
	{
		auto&& exactSolution = Domain(begin, end, count, true, [&](size_t index, double_t coordinate) { return exactSolutionFunction(coordinate); });

		auto&& taggedSolutions = std::map<std::wstring, DifferencedSolution>();
		for (const auto& [tag, solver] : taggedSolvers)
		{
			auto&& solution = solver->Solve(begin, end, fieldFunction, count);
			auto difference = MeterSolutionsDifference(exactSolution, solution);
			taggedSolutions.emplace(tag, DifferencedSolution(std::move(solution), difference));
		}

		return DifferencedSolutions(std::move(exactSolution), std::move(taggedSolutions));
	}

	OrderedSolutions SolutionComparer::MeterSolversOrders(
		double_t begin, double_t end, size_t baseCount,
		const std::map<std::wstring, std::unique_ptr<BaseSolver>>& taggedSolvers,
		const std::function<double_t(double_t)>& fieldFunction,
		const std::function<double_t(double_t)>& exactSolutionFunction,
		const std::vector<size_t>& countMultipliers)
	{
		auto&& baseDifferencedSolutions = MeterSolversDifferences(begin, end, baseCount, taggedSolvers, fieldFunction, exactSolutionFunction);

		auto lastMutiplier = static_cast<size_t>(1);
		auto lastDifferences = std::map<std::wstring, double_t>();
		auto&& exactSolutions = std::map<size_t, Domain>();
		auto&& taggedSolutions = std::map<std::wstring, std::map<size_t, OrderedSolution>>();
		for (auto& [tag, solution] : baseDifferencedSolutions.TaggedDifferencedSolutions)
		{
			lastDifferences.emplace(tag, solution.Difference);
			taggedSolutions.emplace(tag, std::map<size_t, OrderedSolution>());
		};

		for (auto multiplier : countMultipliers)
		{
			auto nextDifferencedSolutions = MeterSolversDifferences(begin, end, baseCount * multiplier, taggedSolvers, fieldFunction, exactSolutionFunction);
			exactSolutions.emplace(multiplier, nextDifferencedSolutions.ExactSolution);
			for (auto& [tag, solution] : taggedSolutions)
			{
				auto nextDifference = nextDifferencedSolutions.TaggedDifferencedSolutions.at(tag).Difference;
				auto accuracyOrder = MeterAccuracyOrder(lastDifferences[tag], nextDifference, static_cast<double_t>(multiplier) / lastMutiplier);
				solution.emplace(multiplier, OrderedSolution(std::move(nextDifferencedSolutions.TaggedDifferencedSolutions.at(tag)), accuracyOrder));

				lastDifferences.at(tag) = nextDifference;
			};

			lastMutiplier = multiplier;
		}

		return OrderedSolutions(std::move(baseDifferencedSolutions), std::move(exactSolutions), std::move(taggedSolutions));
	}

	std::map<std::wstring, double_t> SolutionComparer::MeterSolutionOrders(
		const DifferencedSolutions& coarseSolutions,
		const DifferencedSolutions& accurateSolutions,
		const std::set<std::wstring>& tags,
		double_t multiplier)
	{
		auto&& result = std::map<std::wstring, double_t>();
		for (auto tag : tags)
		{
			auto order = MeterAccuracyOrder(
				coarseSolutions.TaggedDifferencedSolutions.at(tag).Difference,
				accurateSolutions.TaggedDifferencedSolutions.at(tag).Difference,
				multiplier
			);

			result.emplace(tag, order);
		}

		return result;
	}

	double_t SolutionComparer::MeterSolutionsDifference(const Domain& exactSolution, const Domain& calculatedSolution)
	{
		if (exactSolution.Count != calculatedSolution.Count)
		{
			return NAN;
		}

		auto max = 0.;
		for (size_t index = 0; index < exactSolution.Count; ++index)
		{
			max = std::max(max, std::abs(exactSolution.Values[index] - calculatedSolution.Values[index]));
		}

		return max;
	}

	double_t SolutionComparer::MeterAccuracyOrder(double_t coarseDifference, double_t accurateDifference, double_t multiplier)
	{
		return std::log(coarseDifference / accurateDifference) / std::log(multiplier);
	}
}
