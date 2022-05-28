#pragma once
#include "stdafx.h"

namespace NumericMethods
{
	struct Dimension
	{
	public:
		double_t Begin;

		double_t End;

		size_t Count;

		double_t Length;

		double_t Step;

		std::vector<double_t> Coordinates;

	public:
		Dimension(
			double_t begin,
			double_t end,
			size_t count,
			bool createHalfStepOffset
		);

		Dimension(const Dimension&) = default;

		Dimension(Dimension&&) = default;

		Dimension& operator=(const Dimension&) = default;

		Dimension& operator=(Dimension&&) = default;
	};
}
