#include <iostream>
#include <random>
#include <array>
#include <vector>

#include <map>

#include <functional>

#include <string>

class MpGene
{
public:
	std::string name;
	size_t size;

	unsigned char* data;

public:
	MpGene(std::string name, size_t size) : name(name), size(size)
	{
		data = new unsigned char[size];
	}
	~MpGene()
	{
		delete[] data;
	}

	MpGene(const MpGene& copy)
	{
		name = copy.name;
		size = copy.size;

		data = new unsigned char[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = copy.data[i];
		}
	}

	MpGene(MpGene&& copy) noexcept
	{
		name = copy.name;
		size = copy.size;

		data = copy.data;

		copy.name = "";
		copy.size = 0;

		copy.data = nullptr;
	}

	MpGene& operator=(MpGene&& copy) noexcept
	{
		if (this == &copy) return *this;

		delete[] data;

		size = copy.size;
		name = copy.name;
		data = copy.data;

		copy.size = 0;
		copy.name = "";
		copy.data = nullptr;
	}

	void SetupAsBase()
	{
		unsigned char entry;
		for (size_t i = 0; i < size; i++)
		{
			entry = rand() % 256;
			data[i] = entry;

		}
	}

	void VerbosePrint() const
	{
		for (size_t i = 0; i < size; i++)
		{
			int value = (int)data[i];

			std::cout << value;
			if (value < 10)
				std::cout << " ";
			if (value < 100)
				std::cout << " ";
			if (i < size - 1)
				std::cout << " ~ ";
		}
		std::cout << std::endl;
	}

	static void CrossoverOverride(MpGene& target, const MpGene& parent1, const MpGene& parent2)
	{
		if (target.size != parent1.size) return;
		if (target.size != parent2.size) return;

		int selectedParent = 0;
		for (int i = 0; i < target.size; i++)
		{
			selectedParent = rand() % 2;
			target.data[i] = (selectedParent) ? parent1.data[i] : parent2.data[i];
		}
	}

	void Mutate()
	{
		float mutationChance = (float)1 / (float)(size * 10);
		for (int i = 0; i < size; i++)
		{
			float chanceRoll = (float)std::rand() / (float)RAND_MAX;

			if (chanceRoll < mutationChance)
			{
				data[i] = rand() % 256;
			}
		}
	}
};

class MpUnit
{
public:
	std::vector<MpGene> gens;
};

template <size_t S>
float GetFitValue(std::array<int, S> answer, const MpGene& target)
{
	float nominalValue = 1.0f / S;
	float totalFit = 0;
	for (int i = 0; i < S; i++)
	{
		if (answer[i] == target.data[i]) totalFit += nominalValue;
	}

	return totalFit;
}

int main_anon()
{
	std::srand((unsigned int)time(NULL));

	constexpr int initialPopulation = 10;
	constexpr int genSize = 5;
	constexpr int clonesNumber = 1;

	std::array<int, genSize> answer = { 1, 2, 3, 4, 5 };
	bool answerFound = false;

	std::vector<MpUnit> individuals;
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

		std::vector<std::tuple<float, MpUnit*>> fitPairs;
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

				MpGene::CrossoverOverride(std::get<1>(fitPairs[i])->gens[0], std::get<1>(fitPairs[populationHalf + selected1])->gens[0], std::get<1>(fitPairs[populationHalf + selected2])->gens[0]);
			}

			for (int i = populationHalf; i < initialPopulation - clonesNumber; i++)
			{
				individuals[i].gens[0].SetupAsBase();
			}

			for (int i = initialPopulation - clonesNumber; i < initialPopulation; i++)
			{
				individuals[i].gens[0] = MpGene(std::get<1>(fitPairs[i])->gens[0]);
			}
			
			/*
			for (int i = populationHalf; i < initialPopulation - clonesNumber; i++)
			{
				individuals[i].gens[0].SetupAsBase();
			}
			*/

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