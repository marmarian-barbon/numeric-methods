#pragma once
#include "stdafx.h"

#include "Types.h"

namespace NumericMethods
{
	std::function<ValueType(const ValueType& radius)> DerivatedCubicBSpline(double_t smoothingLength);

	std::function<ValueType(const ValueType& radius)> DerivatedTwoSinuses(double_t particleRadius);
}
