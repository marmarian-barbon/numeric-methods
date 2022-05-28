#pragma once
#include "stdafx.h"

#include "Types.h"
#include "Domain.hpp"

namespace NumericMethods
{
	class BaseSolver
	{
	public:
		virtual Domain<ValueType> Solve(const Domain<double_t>& domain) const = 0;

	public:
		virtual ~BaseSolver() = 0;
	};
}
