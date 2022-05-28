#pragma once
#include "stdafx.h"

#include "BaseSolver.hpp"

namespace NumericMethods
{
	class SmoothParticleSolver : public BaseSolver
	{
	private:
		double_t particleRadius;

		std::function<ValueType(ValueType kernel)> derivatedKernel;

	public:
		SmoothParticleSolver(double_t particleSize, std::function<ValueType(ValueType kernel)>&& derivatedKernel);

	public:
		Domain<ValueType> Solve(const Domain<double_t>& domain) const override;
	};
}
