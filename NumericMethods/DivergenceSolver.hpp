#pragma once
#include "stdafx.h"

#include "Domain.hpp"
#include "BaseSolver.hpp"

namespace NumericMethods
{
	class DivergenceSolver : public BaseSolver
	{
	public:
		Domain<ValueType> Solve(const Domain<double_t>& domain) const override;
	};
}
