#include "stdafx.h"

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
}
