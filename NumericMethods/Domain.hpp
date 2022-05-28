#pragma once
#include "stdafx.h"

#include "Dimension.hpp"

namespace NumericMethods
{
	template <class ValueType>
	struct Domain
	{
		using ValueFunction = std::function<ValueType(double_t widthCoordinate, double_t heightCoordinate)>;

		using ValueVector = std::vector<std::vector<ValueType>>;

	public:
		Dimension Height;

		Dimension Width;

		ValueVector Values;

	public:
		Domain(
			const Dimension& height,
			const Dimension& width,
			const ValueFunction& valueFunction) :
			Height(height),
			Width(width),
			Values(createValues(valueFunction))
		{ }

		Domain(
			Dimension&& height,
			Dimension&& width,
			const ValueFunction& valueFunction) :
			Height(std::move(height)),
			Width(std::move(width)),
			Values(createValues(valueFunction))
		{ }

	private:
		ValueVector createValues(const ValueFunction& valueFunction)
		{
			auto result = ValueVector(this->Height.Count);
			for (size_t i = 0; i < this->Height.Count; ++i)
			{
				result[i] = std::vector<ValueType>(this->Width.Count);
				for (size_t j = 0; j < this->Width.Count; ++j)
				{
					result[i][j] = valueFunction(this->Width.Coordinates[j], this->Height.Coordinates[i]);
				}
			}

			return result;
		}
	};
}
