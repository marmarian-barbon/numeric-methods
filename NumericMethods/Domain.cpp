#include "stdafx.h"
#include "Domain.hpp"

namespace NumericMethods
{
	Domain::Domain(
		double_t begin,
		double_t end,
		size_t count,
		bool createHalfStepOffset,
		std::function<double_t(double_t)> const& valuesFunction) :
		Begin(begin),
		End(end),
		Count(count),
		Length(end - begin),
		Points(count),
		Values(count)
	{
		auto steps = this->Count - (createHalfStepOffset ? 0 : 1);
		this->Step = this->Length / steps;

		auto firstPoint = this->Begin + (createHalfStepOffset ? (this->Step / 2) : 0.);
		for (size_t index = 0; index < this->Count; ++index)
		{
			this->Points[index] = firstPoint + (index * this->Step);
			this->Values[index] = valuesFunction(this->Points[index]);
		}
	}
}
