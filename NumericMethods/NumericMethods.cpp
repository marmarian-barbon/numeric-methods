#include "stdafx.h"

#include "Domain.hpp"

using namespace NumericMethods;

int main()
{
	auto domain = Domain(1., 5., 20, true, [](double_t position) { return position; });
}
