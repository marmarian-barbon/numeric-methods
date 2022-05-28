#include "stdafx.h"
#include "SmoothParticleSolver.hpp"

namespace NumericMethods
{
	SmoothParticleSolver::SmoothParticleSolver(double_t particleRadius, std::function<ValueType(ValueType kernel)>&& derivatedKernel) :
		particleRadius(particleRadius),
		derivatedKernel(derivatedKernel)
	{ }

	Domain<ValueType> SmoothParticleSolver::Solve(const Domain<double_t>& domain) const
	{
		auto stepHeight = domain.Height.Step;
		auto additionalHeightSidePointsCount = ptrdiff_t(std::trunc(this->particleRadius / stepHeight));
		auto additionalHeightSidePointsFullCount = size_t(std::abs(additionalHeightSidePointsCount) + 1);
		auto additionalHeightSideFullLength = additionalHeightSidePointsFullCount * stepHeight;

		auto stepWidth = domain.Width.Step;
		auto additionalWidthSidePointsCount = ptrdiff_t(std::trunc(this->particleRadius / stepWidth));
		auto additionalWidthSidePointsFullCount = size_t(std::abs(additionalWidthSidePointsCount) + 1);
		auto additionalWidthSideFullLength = additionalWidthSidePointsFullCount * stepWidth;

		auto constrictDimension = [](const Dimension& expanded, double_t additionalSideFullLength, size_t additionalSidePointsFullCount) {
			return Dimension(
				expanded.Begin + additionalSideFullLength,
				expanded.End - additionalSideFullLength,
				expanded.Count - 1 - (2 * additionalSidePointsFullCount),
				true
			);
		};

		auto volume = stepHeight * stepWidth;

		return Domain<ValueType>(
			constrictDimension(domain.Height, additionalHeightSideFullLength, additionalHeightSidePointsFullCount),
			constrictDimension(domain.Width, additionalWidthSideFullLength, additionalWidthSidePointsFullCount),
			[this, particleRadius = this->particleRadius, volume, &domain](double_t widthCoordinate, double_t heightCoordinate)
			{
				auto result = ValueType({ 0, 0 });
				for (size_t i = 0; i < domain.Height.Count; ++i)
				{
					if (std::abs(heightCoordinate - domain.Height.Coordinates[i]) > particleRadius)
					{
						continue;
					}

					for (size_t j = 0; j < domain.Width.Count; ++j)
					{
						if (std::abs(widthCoordinate - domain.Width.Coordinates[j]) > particleRadius)
						{
							continue;
						}

						auto cellDerivative = this->derivatedKernel({
							widthCoordinate - domain.Width.Coordinates[j],
							heightCoordinate - domain.Height.Coordinates[i],
						});

						result[0] += domain.Values[i][j] * cellDerivative[0];
						result[1] += domain.Values[i][j] * cellDerivative[1];
					}
				}

				return ValueType({ result[0] * volume, result[1] * volume });
			}
		);
	}
}
