#pragma once
#include "stdafx.h"

#include "BaseSolver.hpp"

namespace NumericMethods
{
	class SmoothParticleSolver : public BaseSolver
	{
	private:
		double_t particleRadius;

		std::function<double_t(double_t kernel)> derivatedKernel;

	public:
		SmoothParticleSolver(double_t particleSize, std::function<double_t(double_t kernel)>&& derivatedKernel);

	public:
		Domain Solve(double_t begin, double_t end, const std::function<double_t(double_t)>& fieldFunction, size_t count) const override;
	};
}
