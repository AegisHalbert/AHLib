#include "StringOps.h"
#include "MathOps.h"

#include <iostream>
#include <thread>

/*
*	Given a set of N strings, find the average char value, but only taking alphabetic characters into accout
*	Afterwards, print the first alphabetic character for the string with the lowest average and the last
*	alphabetic character for the string with the highest average
*/

static std::vector<int> averageResults;
static void AverageForSingleString(const char* input, int index)
{
	const char* onlyAlphabetic = AHLib::ChopString(input, AHLib::IsAlphabetical);
	averageResults[index] = AHLib::AverageInt(onlyAlphabetic);
}

int main_221222()
{
	int sampleSize = 8;

	averageResults.reserve(sampleSize);
	for (int i = 0; i < sampleSize; i++)
	{
		averageResults.emplace_back(0);
	}

	std::vector<const char*> charSeries;
	charSeries.reserve(sampleSize);

	charSeries.emplace_back("ok?g");
	charSeries.emplace_back("88217345a5g7m9");
	charSeries.emplace_back("Chamomile");
	charSeries.emplace_back("S3ym0ur");
	charSeries.emplace_back("directionsLuncheon");
	charSeries.emplace_back("-???----");
	charSeries.emplace_back("str33med");
	charSeries.emplace_back("44hans7fflammenwerfer");

	std::vector<std::thread> allThreads;
	allThreads.reserve(sampleSize);
	for (int i = 0; i < sampleSize; i++)
	{
		allThreads.emplace_back(std::thread(AverageForSingleString, charSeries[i], i));
	}

	for (int i = 0; i < sampleSize; i++) 
	{
		allThreads[i].join();
	}

	for (int i = 0; i < sampleSize; i++)
	{
		std::cout << "Average value for " << charSeries[i] << ": " << averageResults[i] << std::endl;
	}
	std::cout << "----------" << std::endl << std::endl;

	int minIndex = -1;
	int minValue = 256;
	int maxIndex = -1;
	int maxValue = 0;
	for (int i = 0; i < sampleSize; i++)
	{
		int averageValue = averageResults[i];

		if (averageValue < minValue)
		{
			minIndex = i;
			minValue = averageValue;
		}
		if (averageValue > maxValue)
		{
			maxIndex = i;
			maxValue = averageValue;
		}
	}

	std::string selectedMin = charSeries[minIndex];
	std::string selectedMax = charSeries[maxIndex];

	std::string::iterator charItResult;
	std::string::iterator charItForwardEnd = selectedMin.end();

	charItResult = std::find_if(selectedMin.begin(), charItForwardEnd, AHLib::IsAlphabetical);

	if (charItResult != charItForwardEnd) std::cout << "Character for min average[" << selectedMin << "]: " << *charItResult << std::endl;
	else std::cout << "The string with the lowest average has no alphabetic chars" << std::endl;

	std::string::iterator charItBackwards = selectedMax.end();
	charItBackwards--;
	char charPrintedMax = 0;
	while (charItBackwards != selectedMax.begin())
	{
		if (AHLib::IsAlphabetical(*charItBackwards))
		{
			charPrintedMax = *charItBackwards;
			break;
		}
		charItBackwards--;
	}

	std::cout << "Character for min average[" << selectedMax << "]: " << charPrintedMax << std::endl;

	return 0;
}