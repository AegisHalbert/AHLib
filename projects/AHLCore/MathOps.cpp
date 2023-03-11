#include <Core/MathOps.h>

namespace ahl
{
	int AverageInt(const std::vector<int>& input)
	{
		int elementCount = input.capacity();
		if (elementCount == 0) return 0;

		int totalValue = 0;
		for (int element : input)
			totalValue += element;

		return totalValue / elementCount;
	}
	int AverageInt(const char* input)
	{
		int elementCount = strlen(input);
		if (elementCount == 0) return 0;

		int totalValue = 0;
		for (int i = 0; i < elementCount; i++)
			totalValue += (int)input[i];

		return totalValue / elementCount;
	}
}