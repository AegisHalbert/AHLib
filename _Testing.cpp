#include "Structures.h";

int main()
{
	AHLib::Darray<std::string> data;
	data.Add("yo");
	data.Add("this");
	data.Add("is");
	data.Add("quite");
	data.Add("weird");

	for (std::string entry : data)
	{
		std::cout << entry << std::endl;
	}

	return 0;
}