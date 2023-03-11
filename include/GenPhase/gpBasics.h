#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace ahl
{
	class MpGene
	{
	public:
		std::string name;
		size_t size;

		unsigned char* data;

	public:
		MpGene(std::string name, size_t size);
		~MpGene();

		MpGene(const MpGene& copy);
		MpGene(MpGene&& copy) noexcept;

		MpGene& operator=(MpGene&& copy) noexcept;

		void SetupAsBase();
		static void CrossoverOverride(MpGene& target, const MpGene& parent1, const MpGene& parent2);
		void Mutate();

		void VerbosePrint() const;
	};

	class MpUnit
	{
	public:
		std::vector<MpGene> gens;
	};
}