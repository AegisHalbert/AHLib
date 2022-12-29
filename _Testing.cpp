#include "Structures.h"
#include "Benchmark.h"

#include <iostream>
#include <array>

int main()
{
	AHLib::Darray<int> data;

	data.Add(7);
	data.Add(9);
	data.Add(4);

	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	data.Clear(false);

	{
		// REMOVE THIS LINE - MULTIPLE DEFINITIONS FOUND
		AHLib::ScopeWatch();
		// --- //

		for (int i = 0; i < data.Count(); i++)
		{
			std::cout << data[i] << std::endl;
		}

		data.Add(1);
		data.Add(1);
		data.Add(1);
	}

	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	return 0;
}