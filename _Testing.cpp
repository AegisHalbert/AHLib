#include "Structures.h"

#include <iostream>
#include <array>

int main()
{
	AHLib::Darray<int> data;
	
	// Remove method in Darray is NOT finished

	data.Add(7);
	data.Add(9);
	data.Add(4);

	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	data.Remove(9);

	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	return 0;
}