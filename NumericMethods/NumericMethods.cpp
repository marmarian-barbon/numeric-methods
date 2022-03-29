#include "stdafx.h"

#include <iostream>
#include <format>

#include "Domain.hpp"
#include "DivergenceSolver.hpp"
#include "SmoothParticleSolver.hpp"
#include "Kernels.h"
#include "SolutionComparer.hpp"

using namespace NumericMethods;

int main()
{
	auto begin = 5.;
	auto end = 9.;
	auto count = 100;
	auto particleRadius = 1.;

	auto fieldFunction = [](double_t position) {
		return std::log(position);
	};

	auto divergenceFunction = [](double_t position) {
		return 1 / position;
	};

	auto solvers = std::map<std::wstring, std::unique_ptr<BaseSolver>>();
	solvers.emplace(L"divergence", std::make_unique<DivergenceSolver>(DivergenceSolver()));
	solvers.emplace(L"smooth", std::make_unique<SmoothParticleSolver>(SmoothParticleSolver(particleRadius, DerivatedCubicBSpline(particleRadius / 2))));

	std::wcout << L"|       |               divergence |          smooth particle |\n";
	std::wcout << L"| count |   difference |     order |   difference |     order |\n";

	auto baseResult = SolutionComparer::MeterSolversDifferences(begin, end, count, solvers, fieldFunction, divergenceFunction);

	std::wcout << std::format(
		L"| {0:5} | {1:12.7f} | {2:>9} | {3:12.7f} | {4:>9} |\n",
		baseResult.ExactSolution.Count,
		baseResult.TaggedDifferencedSolutions.at(L"divergence").Difference,
		L"base",
		baseResult.TaggedDifferencedSolutions.at(L"smooth").Difference,
		L"base"
	);

	auto tags = std::set<std::wstring>({ L"divergence" , L"smooth" });
	auto multipliers = std::vector<size_t>({ 2, 4, 8, 16 });
	auto& lastResult = baseResult;
	auto lastMultiplier = 1.;

	for (auto multiplier : multipliers)
	{
		solvers = std::map<std::wstring, std::unique_ptr<BaseSolver>>();
		solvers.emplace(L"divergence", std::make_unique<DivergenceSolver>(DivergenceSolver()));
		solvers.emplace(L"smooth", std::make_unique<SmoothParticleSolver>(SmoothParticleSolver(particleRadius, DerivatedCubicBSpline(particleRadius / (2 * multiplier)))));

		auto multipliedResult = SolutionComparer::MeterSolversDifferences(begin, end, count * multiplier, solvers, fieldFunction, divergenceFunction);

		auto orders = SolutionComparer::MeterSolutionOrders(baseResult, multipliedResult, tags, multiplier / lastMultiplier);

		std::wcout << std::format(
			L"| {0:5} | {1:12.7f} | {2:9.6f} | {3:12.7f} | {4:9.6f} |\n",
			multipliedResult.ExactSolution.Count,
			multipliedResult.TaggedDifferencedSolutions.at(L"divergence").Difference,
			orders.at(L"divergence"),
			multipliedResult.TaggedDifferencedSolutions.at(L"smooth").Difference,
			orders.at(L"smooth")
		);

		lastResult = multipliedResult;
		lastMultiplier = static_cast<double_t>(multiplier);
	}
}
