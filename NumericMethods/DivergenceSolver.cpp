#include "stdafx.h"
#include "DivergenceSolver.hpp"

namespace NumericMethods
{
	Domain DivergenceSolver::Solve(double_t begin, double_t end, const std::function<double_t(double_t)>& fieldFunction, size_t count) const
	{
		auto field = Domain(begin, end, count + 1, false, [&](size_t index, double_t coordinate) { return fieldFunction(coordinate); });
		return Domain(begin, end, count, true, [&](size_t index, double_t coordinate) {
			return (field.Values[index + 1] - field.Values[index]) / field.Step;
		});
	}
}
