#include <GenPhase/polyrunner.h>

#include <iostream>

static int Testpolyrunner()
{
	std::queue<int> callSequence;
	callSequence.push(0);
	callSequence.push(4);
	callSequence.push(2);
	callSequence.push(0);
	callSequence.push(0);
	callSequence.push(2);
	callSequence.push(4);

	float& liquidX1 = *(new float(5));
	float& liquidX2 = *(new float(10));
	float& liquidX3 = *(new float(15));

	float result1 = ahl::PolyRunner(liquidX1, callSequence);
	float result2 = ahl::PolyRunner(liquidX2, callSequence);
	float result3 = ahl::PolyRunner(liquidX3, callSequence);

	liquidX1 = 7;
	liquidX2 = -12;
	liquidX3 = 3;

	float result4 = ahl::PolyRunner(liquidX1, callSequence);
	float result5 = ahl::PolyRunner(liquidX2, callSequence);
	float result6 = ahl::PolyRunner(liquidX3, callSequence);

	std::cout << result1 << std::endl;
	std::cout << result2 << std::endl;
	std::cout << result3 << std::endl;
	std::cout << result4 << std::endl;
	std::cout << result5 << std::endl;
	std::cout << result6 << std::endl;

	return 0;

	return 0;
}