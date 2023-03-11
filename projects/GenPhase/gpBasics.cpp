#include <GenPhase/gpBasics.h>

namespace ahl
{
	MpGene::MpGene(std::string name, size_t size) : name(name), size(size)
	{
		data = new unsigned char[size];
	}
	MpGene::~MpGene()
	{
		delete[] data;
	}

	MpGene::MpGene(const MpGene& copy)
	{
		name = copy.name;
		size = copy.size;

		data = new unsigned char[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = copy.data[i];
		}
	}
	MpGene::MpGene(MpGene&& copy) noexcept
	{
		name = copy.name;
		size = copy.size;

		data = copy.data;

		copy.name = "";
		copy.size = 0;

		copy.data = nullptr;
	}

	MpGene& MpGene::operator=(MpGene&& copy) noexcept
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

	void MpGene::SetupAsBase()
	{
		unsigned char entry;
		for (size_t i = 0; i < size; i++)
		{
			entry = rand() % 256;
			data[i] = entry;

		}
	}

	void MpGene::VerbosePrint() const
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

	void MpGene::CrossoverOverride(MpGene& target, const MpGene& parent1, const MpGene& parent2)
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

	void MpGene::Mutate()
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