#pragma once
#include "stdafx.h"

namespace NumericMethods
{
	std::function<double_t(double_t radius)> DerivatedCubicBSpline(double_t smoothingLength);
}
