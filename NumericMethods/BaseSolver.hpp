#pragma once
#include "stdafx.h"

#include "Domain.hpp"

namespace NumericMethods
{
	class BaseSolver
	{
	public:
		virtual Domain Solve(double_t begin, double_t end, const std::function<double_t(double_t)>& fieldFunction, size_t count) const = 0;

	public:
		virtual ~BaseSolver() = 0;
	};
}
