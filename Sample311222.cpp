#include "Structures.h"
#include "Benchmark.h"

#include <iostream>
#include <array>

/*
*	While creating a simple Dynamic array class, the Clear() function was implemented to remove all
*	the elements. A bool variable is included to optionally keep the old pointers reference and
*	actually keep the data until a method like Add() overwrites it (but losing the count of items).
*	Using the ScopeWatch class, it's measured how much time is saved by recycling the pointer.
* 
*	Keeping the pointer on clear would take a maximum of 25ms to fill it again
*	Discarding the pointer, and thus making the class resize for each call of Add would return
*	something between 250ms and 850ms
* 
*	Of course it needs to be kept in mind that this implementation of Dynamic array has a resizing
*	method that is extremely unoptimized (AHLib-0.0.1)
*/

int main_311222()
{
	AHLib::Darray<int> data;
	data.Add(1);
	data.Add(0);
	data.Add(0);
	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	data.Clear(false);
	{
		AHLib::ScopeWatch watch("Pointer Kept on Clear");

		data.Add(0);
		data.Add(1);
		data.Add(0);
	}
	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	data.Clear(true);
	{
		AHLib::ScopeWatch watch("Pointer Freed on Clear");

		data.Add(0);
		data.Add(0);
		data.Add(1);
	}
	for (int i = 0; i < data.Count(); i++)
	{
		std::cout << data[i] << std::endl;
	}

	return 0;
}