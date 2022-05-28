#include "stdafx.h"
#include "Kernels.h"

namespace NumericMethods
{
	ValueType scaleVector(double_t scalar, const ValueType& vector)
	{
		return ValueType({ vector[0] * scalar, vector[1] * scalar });
	}

	std::function<ValueType(const ValueType& radius)> DerivatedCubicBSpline(double_t particleRadius)
	{
		auto smoothingLength = particleRadius / 2;
		constexpr auto core = 15. / (7. * std::numbers::pi_v<double_t>);
		auto main = core / std::pow(smoothingLength, 3.);

		return [=](ValueType radius) {
			auto length = std::sqrt(
				(radius[0] * radius[0]) +
				(radius[1] * radius[1])
			);

			auto smoothedLength = length / smoothingLength;

			if (smoothedLength <= 1) {
				return scaleVector((main / length) * ((-2. * smoothedLength) + ((3. / 2.) * std::pow(smoothedLength, 2.))), radius);
			}

			if (smoothedLength <= 2) {
				return scaleVector((main / length) * (-1. / 2.) * std::pow(2. - smoothedLength, 2), radius);
			}

			return ValueType({ 0., 0. });
		};
	}

	std::function<ValueType(const ValueType& radius)> DerivatedTwoSinuses(double_t particleRadius)
	{
		auto pi = std::numbers::pi_v<double_t>;
		auto k = 2.;
		auto h = particleRadius / k;
		auto core = pi / (((3 * pi * pi) - 16) * std::pow(k * h, 2));
		auto main = core / h;

		return [=](ValueType radius) {
			auto length = std::sqrt(
				(radius[0] * radius[0]) +
				(radius[1] * radius[1])
			);

			auto q = length / h;

			if (q <= k) {
				return scaleVector((main / length) * (-2 * pi * (std::sin(2 * pi * q / k) + (2 * std::sin(pi * q / k))) / k), radius);
			}

			return ValueType({ 0., 0. });
		};
	}
}
