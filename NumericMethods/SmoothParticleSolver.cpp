#include "stdafx.h"
#include "SmoothParticleSolver.hpp"

#include "Kernels.h"

namespace NumericMethods
{
	SmoothParticleSolver::SmoothParticleSolver(double_t particleRadius, std::function<double_t(double_t kernel)>&& derivatedKernel) :
		particleRadius(particleRadius),
		derivatedKernel(derivatedKernel)
	{ }

	Domain SmoothParticleSolver::Solve(double_t begin, double_t end, const std::function<double_t(double_t)>& fieldFunction, size_t count) const
	{
		auto step = (end - begin) / count;
		auto additionalSidePointsCount = static_cast<ptrdiff_t>(std::trunc(this->particleRadius / step));
		auto additionalSidePointsFullCount = static_cast<size_t>(std::abs(additionalSidePointsCount) + 1);
		auto additionalSideFullLength = additionalSidePointsFullCount * step;

		auto field = Domain(
			begin - additionalSideFullLength,
			end + additionalSideFullLength,
			count + 1 + (2 * additionalSidePointsFullCount),
			false,
			[&](size_t index, double_t coordinate) { return fieldFunction(coordinate); }
		);

		auto calculatedDerivatedKernel = std::vector<double_t>(additionalSidePointsFullCount);
		for (size_t overIndex = 0; overIndex < additionalSidePointsFullCount; ++overIndex)
		{
			auto positiveRadius = (overIndex + 0.5) * field.Step;
			calculatedDerivatedKernel[overIndex] = this->derivatedKernel(positiveRadius);
		}

		return Domain(
			begin,
			end,
			count,
			true,
			[&calculatedDerivatedKernel, &field, coveredPointsCount = additionalSidePointsFullCount](size_t index, double_t coordinate) {
				auto result = 0.;
				auto interestParticleIndex = coveredPointsCount + index;
				for (auto neighbourParticleIndexShift = 0; neighbourParticleIndexShift < coveredPointsCount; ++neighbourParticleIndexShift)
				{
					result += field.Values[interestParticleIndex - neighbourParticleIndexShift] * calculatedDerivatedKernel[neighbourParticleIndexShift];
					result -= field.Values[interestParticleIndex + 1 + neighbourParticleIndexShift] * calculatedDerivatedKernel[neighbourParticleIndexShift];
				}

				return result * field.Step;
			}
		);
	}
}
