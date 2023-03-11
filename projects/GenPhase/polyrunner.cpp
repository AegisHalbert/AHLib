#include <GenPhase/polyrunner.h>

namespace ahl
{
	float ElementalOperate(int operatorValue, float& liquidVariable, float constantValue)
	{
		switch (operatorValue)
		{
		case 0: return std::cos(liquidVariable * constantValue);
		case 1: return std::sin(liquidVariable * constantValue);
		case 2: return std::tan(liquidVariable * constantValue);
		case 3: return std::acos(liquidVariable * constantValue);
		case 4: return std::asin(liquidVariable * constantValue);
		case 5: return std::atan(liquidVariable * constantValue);
		case 6: return std::cosh(liquidVariable * constantValue);
		case 7: return std::sinh(liquidVariable * constantValue);
		case 8: return std::tanh(liquidVariable * constantValue);
		case 9: return std::acosh(liquidVariable * constantValue);
		case 10: return std::asinh(liquidVariable * constantValue);
		case 11: return std::atanh(liquidVariable * constantValue);
		case 12: return std::exp(liquidVariable * constantValue);
		case 13: return std::log(liquidVariable * constantValue);
		case 14: return std::log10(liquidVariable * constantValue);
		case 15: return std::pow(liquidVariable, constantValue);
		case 16: return std::pow(constantValue, liquidVariable);
		case 17: return constantValue + liquidVariable;
		case 18: return constantValue * liquidVariable;
		}
	}

	float PolyRunner(float& liquidVariable, std::queue<int> chainCall)
	{
		int operatorValue = chainCall.front();
		chainCall.pop();

		float constantValue = 0;

		int a = chainCall.front();
		chainCall.pop();
		int b = chainCall.front();
		chainCall.pop();

		constantValue = (float)a / (float)b;

		if (!chainCall.empty())
		{
			int interOperator = chainCall.front();
			chainCall.pop();

			float resultValue = ElementalOperate(operatorValue, liquidVariable, constantValue);

			switch (interOperator)
			{
			case 0: return resultValue + PolyRunner(liquidVariable, chainCall);
			case 1: return resultValue * PolyRunner(liquidVariable, chainCall);
			case 2: return std::pow(resultValue, PolyRunner(liquidVariable, chainCall));
			case 3: return std::pow(PolyRunner(liquidVariable, chainCall), resultValue);
			}
		}
		else
		{
			return ElementalOperate(operatorValue, liquidVariable, constantValue);
		}
	}
}