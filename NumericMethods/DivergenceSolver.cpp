#include "stdafx.h"
#include "DivergenceSolver.hpp"

namespace NumericMethods
{
	Domain<ValueType> DivergenceSolver::Solve(const Domain<double_t>& domain) const
	{
		auto result = Domain<ValueType>(
			Dimension(domain.Width.Begin, domain.Width.End, domain.Width.Count - 1, true),
			Dimension(domain.Height.Begin, domain.Height.End, domain.Height.Count - 1, true),
			[](double_t widthCoordinate, double_t heightCoordinate) {
				return ValueType({ 0., 0. });
			}
		);

		for (size_t i = 0; i < result.Height.Count; ++i)
		{
			for (size_t j = 0; j < result.Width.Count; ++j)
			{
				result.Values[i][j][0] = (
					(domain.Values[i][j + 1] + domain.Values[i + 1][j + 1]) - (domain.Values[i][j] + domain.Values[i + 1][j])
				) / (domain.Width.Step * 2);
				result.Values[i][j][1] = (
					(domain.Values[i + 1][j] + domain.Values[i + 1][j + 1]) - (domain.Values[i][j] + domain.Values[i][j + 1])
				) / (domain.Height.Step * 2);
			}
		}

		return result;
	}
}
