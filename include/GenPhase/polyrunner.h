#pragma once

#include <cmath>
#include <queue>

namespace ahl
{
	float ElementalOperate(int operatorValue, float& liquidVariable, float constantValue);

	float PolyRunner(float& liquidVariable, std::queue<int> chainCall);
}