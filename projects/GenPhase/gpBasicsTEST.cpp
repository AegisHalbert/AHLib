#include <GenPhase/gpBasics.h>

#include <array>
#include <vector>
#include <functional>
#include <random>

template <size_t S>
float GetFitValue(std::array<int, S> answer, const ahl::MpGene& target)
{
	float nominalValue = 1.0f / S;
	float totalFit = 0;
	for (int i = 0; i < S; i++)
	{
		if (answer[i] == target.data[i]) totalFit += nominalValue;
	}

	return totalFit;
}

static int TestgpBasics()
{
	std::srand((unsigned int)time(NULL));

	constexpr int initialPopulation = 10;
	constexpr int genSize = 5;
	constexpr int clonesNumber = 1;

	std::array<int, genSize> answer = { 1, 2, 3, 4, 5 };
	bool answerFound = false;

	std::vector<ahl::MpUnit> individuals;
	individuals.reserve(initialPopulation);

	std::cout << "Generation: " << 0 << std::endl;

	for (int i = 0; i < initialPopulation; i++)
	{
		individuals.emplace_back();
		individuals[i].gens.emplace_back("sample" + std::to_string(i), genSize);
		individuals[i].gens[0].SetupAsBase();
	}

	for (int i = 0; i < initialPopulation; i++)
	{
		individuals[i].gens[0].VerbosePrint();
	}

	std::cout << std::endl;

	int generationCount = 1;

	while (!answerFound)
	{
		std::cout << "Generation: " << generationCount << std::endl;

		std::vector<std::tuple<float, ahl::MpUnit*>> fitPairs;
		fitPairs.reserve(initialPopulation);

		for (int i = 0; i < initialPopulation; i++)
		{
			fitPairs.push_back(std::make_tuple(GetFitValue(answer, individuals[i].gens[0]), &individuals[i]));
		}

		std::sort(fitPairs.begin(), fitPairs.end());

		for (int i = initialPopulation - 1; i >= 0; i--)
		{
			if (std::get<0>(fitPairs[i]) >= 0.95f)
			{
				answerFound = true;
				break;
			}
		}

		if (!answerFound)
		{
			int populationHalf = initialPopulation / 2;

			int selected1;
			int selected2;
			for (int i = 0; i < (populationHalf); i++)
			{
				selected1 = std::rand() % populationHalf;
				selected2 = selected1;
				while (selected1 == selected2)
				{
					selected2 = std::rand() % populationHalf;
				}

				ahl::MpGene::CrossoverOverride(std::get<1>(fitPairs[i])->gens[0], std::get<1>(fitPairs[populationHalf + selected1])->gens[0], std::get<1>(fitPairs[populationHalf + selected2])->gens[0]);
			}

			for (int i = populationHalf; i < initialPopulation - clonesNumber; i++)
			{
				individuals[i].gens[0].SetupAsBase();
			}

			for (int i = initialPopulation - clonesNumber; i < initialPopulation; i++)
			{
				individuals[i].gens[0] = ahl::MpGene(std::get<1>(fitPairs[i])->gens[0]);
			}

			for (int i = 0; i < individuals.size(); i++)
			{
				individuals[i].gens[0].Mutate();
			}
		}

		for (int i = 0; i < individuals.size(); i++)
		{
			individuals[i].gens[0].VerbosePrint();
		}

		if ((generationCount == 1) || (generationCount % 1000000) == 0 || answerFound)
		{
			if (answerFound) std::cout << "Final generation: " << generationCount << std::endl;
			std::cin.get();
		}
		generationCount++;
	}

	return 0;
}