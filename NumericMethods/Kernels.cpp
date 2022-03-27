#include "stdafx.h"
#include "Kernels.h"

namespace NumericMethods
{
	std::function<double_t(double_t radius)> DerivatedCubicBSpline(double_t smoothingLength)
	{
		auto main = (1 / smoothingLength) / smoothingLength;

		return [=](double_t radius) {
			auto smoothedRadius = radius / smoothingLength;
			auto sign = smoothedRadius >= 0
				? +1.
				: -1.;

			auto smoothedLength = std::abs(sign * smoothedRadius);

			if (smoothedLength < 1) {
				return sign * main * ((-2. * smoothedLength) + ((3. / 2.) * std::pow(smoothedLength, 2.)));
			}

			if (smoothedLength < 2) {
				return sign * main * (-1. / 2.) * std::pow(2. - smoothedLength, 2);
			}

			return 0.;
		};
	}
}
