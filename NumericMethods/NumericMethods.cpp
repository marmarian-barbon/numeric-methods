#include "stdafx.h"

#include <iostream>
#include <format>

#include "Dimension.hpp"
#include "Domain.hpp"
#include "SmoothParticleSolver.hpp"
#include "DivergenceSolver.hpp"
#include "Kernels.h"
#include "SolutionComparer.hpp"

using namespace NumericMethods;

int main()
{
	auto begin = 5.;
	auto end = 9.;
	auto baseCount = 50;
	auto baseParticleRadius = 0.991;

	auto divergenceTag = L"Gauss";
	auto smoothParticleTag = L"SPH";
	auto tags = std::set<std::wstring>({ divergenceTag, smoothParticleTag });

	auto function = [](double_t widthCoordinate, double_t heightCoordinate) {
		return std::log(widthCoordinate) * std::log(heightCoordinate);
	};

	auto divergence = std::function<ValueType(double_t widthCoordinate, double_t heightCoordinate)>([](double_t widthCoordinate, double_t heightCoordinate) {
		return ValueType({ std::log(heightCoordinate) / widthCoordinate, std::log(widthCoordinate) / heightCoordinate });
	});

	auto multipliers = std::vector<size_t>({ 2, 2, 2 });

	auto expandDimension = [](const Dimension& base, double_t particleRadius) {
		auto step = base.Step;
		auto additionalSidePointsCount = ptrdiff_t(std::trunc(particleRadius / step));
		auto additionalSidePointsFullCount = size_t(std::abs(additionalSidePointsCount) + 1);
		auto additionalSideFullLength = additionalSidePointsFullCount * step;

		return Dimension(
			base.Begin - additionalSideFullLength,
			base.End + additionalSideFullLength,
			base.Count + (2 * additionalSidePointsFullCount),
			false
		);
	};

	auto calculateDifferences = [begin, end, baseCount, baseParticleRadius, divergenceTag, smoothParticleTag, &tags, &function, &divergence, &expandDimension](size_t multiplier)
	{
		auto count = baseCount * multiplier;
		auto particleRadius = baseParticleRadius / multiplier;

		auto domain = Domain<double_t>(
			Dimension(begin, end, count + 1, false),
			Dimension(begin, end, count + 1, false),
			function
		);

		auto expandedDomain = Domain<double_t>(
			expandDimension(domain.Height, particleRadius),
			expandDimension(domain.Width, particleRadius),
			function
		);

		auto divergenceSolver = DivergenceSolver();
		auto smoothParticleSolver = SmoothParticleSolver(particleRadius, DerivatedTwoSinuses(particleRadius));

		auto taggedSolutions = std::map<std::wstring, std::unique_ptr<Domain<ValueType>>>();
		taggedSolutions.emplace(divergenceTag, std::make_unique<Domain<ValueType>>(divergenceSolver.Solve(domain)));
		taggedSolutions.emplace(smoothParticleTag, std::make_unique<Domain<ValueType>>(smoothParticleSolver.Solve(expandedDomain)));

		auto taggedDifferences = SolutionComparer::MeterSolversDifferences(tags, domain, divergence, taggedSolutions);

		return taggedDifferences;
	};

	std::wcout << L"|         |               divergence |          smooth particle |\n";
	std::wcout << L"|  count  |   difference |     order |   difference |     order |\n";
	auto baseDifferences = calculateDifferences(1);
	std::wcout << std::format(
		L"| {0:3}x{1:3} | {2:12.7f} | {3:>9} | {4:12.7f} | {5:>9} |\n",
		baseCount,
		baseCount,
		baseDifferences.at(divergenceTag),
		L"base",
		baseDifferences.at(smoothParticleTag),
		L"base"
	);

	auto lastDifferences = std::map<std::wstring, double_t>(std::move(baseDifferences));
	auto lastMultiplier = size_t(1);
	for (auto multiplier : multipliers)
	{
		auto totalMultiplier = lastMultiplier * multiplier;
		auto differences = calculateDifferences(totalMultiplier);
		auto orders = SolutionComparer::MeterSolutionOrders(tags, lastDifferences, differences, multiplier);
		std::wcout << std::format(
			L"| {0:>3}x{1:<3} | {2:12.7f} | {3:9.6f} | {4:12.7f} | {5:9.6f} |\n",
			baseCount * totalMultiplier,
			baseCount * totalMultiplier,
			differences.at(divergenceTag),
			orders.at(divergenceTag),
			differences.at(smoothParticleTag),
			orders.at(smoothParticleTag)
		);

		lastDifferences = std::move(differences);
		lastMultiplier = totalMultiplier;
	}

	std::wcout << "solved" << std::endl;
}
