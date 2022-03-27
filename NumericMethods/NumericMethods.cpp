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
	auto count = 20;
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

	auto multipliers = std::vector<size_t>({2, 4, 8, 16});

	auto result = SolutionComparer::MeterSolversOrders(begin, end, count, solvers, fieldFunction, divergenceFunction, multipliers);

	std::wcout << L"| count |               divergence |          smooth particle |\n";
	std::wcout << L"| count |   difference |     order |   difference |     order |\n";
	std::wcout << std::format(
		L"| {0:5} | {1:12.7f} | {2:>9} | {3:12.7f} | {4:>9} |\n",
		result.ExactSolution.Count,
		result.TaggedDifferencedSolutions.at(L"divergence").Difference,
		L"base",
		result.TaggedDifferencedSolutions.at(L"smooth").Difference,
		L"base"
	);

	for (auto multiplier : multipliers)
	{
		std::wcout << std::format(
			L"| {0:5} | {1:12.7f} | {2:9.6f} | {3:12.7f} | {4:9.6f} |\n",
			result.ExactOrderedSolutions.at(multiplier).Count,
			result.TaggedOrderedSolutions.at(L"divergence").at(multiplier).Difference,
			result.TaggedOrderedSolutions.at(L"divergence").at(multiplier).Order,
			result.TaggedOrderedSolutions.at(L"smooth").at(multiplier).Difference,
			result.TaggedOrderedSolutions.at(L"smooth").at(multiplier).Order
		);
	}
}
