#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "BaseSolver.hpp"

namespace NumericMethods
{
	class DivergenceSolver : public BaseSolver
	{
	public:
		Domain Solve(double_t begin, double_t end, const std::function<double_t(double_t)>& fieldFunction, size_t count) const override;
	};
}
