#pragma once
#include "stdafx.h"

namespace NumericMethods
{
	struct Domain
	{
	public:
		double_t Begin;

		double_t End;

		size_t Count;

		double_t Length;

		double_t Step;

		std::vector<double_t> Points;

		std::vector<double_t> Values;

	public:
		Domain(
			double_t begin,
			double_t end,
			size_t count,
			bool createHalfStepOffset,
			std::function<double_t(double_t)> const& valuesFunction
		);
	};
}
