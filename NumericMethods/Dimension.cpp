#include "stdafx.h"
#include "Dimension.hpp"

namespace NumericMethods
{
	Dimension::Dimension(
		double_t begin,
		double_t end,
		size_t count,
		bool createHalfStepOffset) :
		Begin(begin),
		End(end),
		Count(count),
		Length(End - Begin),
		Step(Length / (Count - (createHalfStepOffset ? 0 : 1))),
		Coordinates(Count)
	{
		auto firstCoordinate = this->Begin + (createHalfStepOffset ? this->Step / 2 : 0.);

		for (size_t index = 0; index < this->Count; ++index)
		{
			this->Coordinates[index] = firstCoordinate + (index * this->Step);
		}
	}
}
