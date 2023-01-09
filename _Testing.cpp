#include "Structures.h";

int main()
{
	AHLib::Darray<int> data;
	data.Add(1);
	data.Add(0);
	data.Add(0);
	data.Add(5);
	data.Add(4);

	for (int entry : data)
	{
		std::cout << entry << std::endl;
	}

	return 0;
}