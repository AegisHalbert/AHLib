#include <iostream>
#include <filesystem>
#include <string>

static const std::string CONFIGFILENAME = "config.txt";

std::ostream& operator<<(std::ostream& stream, const std::filesystem::file_time_type time)
{
	stream << time.time_since_epoch().count();
	return stream;
}

static void PrintPathContent(std::filesystem::path workingPath, bool recursive = false)
{
	std::cout << "-----PATH-CONTENT-----" << std::endl;

	std::filesystem::directory_entry workingDirectory(workingPath);

	if (recursive)
	{
		std::filesystem::recursive_directory_iterator directoryIterate(workingDirectory);
		for (std::filesystem::directory_entry entry : directoryIterate)
		{
			std::cout << entry.path().filename() << std::endl;
		}
	}
	else
	{
		std::filesystem::directory_iterator directoryIterate(workingDirectory);
		for (std::filesystem::directory_entry entry : directoryIterate)
		{
			std::cout << entry.path().filename() << std::endl;
		}
	}
	
}

int main()
{
	std::filesystem::path workingPath = std::filesystem::current_path();

	std::cout << "BOOT AT: ";
	std::cout << workingPath << std::endl;
	std::cout << "----------------------" << std::endl;
	
	std::filesystem::directory_entry workingDirectory(workingPath);
	std::filesystem::directory_iterator directoryIterate(workingDirectory);

	PrintPathContent(workingPath);

	bool configFound = false;
	for (std::filesystem::directory_entry entry : directoryIterate)
	{
		if (entry.path().filename() == CONFIGFILENAME)
		{
			configFound = true;
			break;
		}
	}

	std::cout << "Configuration found: " << configFound << std::endl;

	std::cout << std::endl;
	std::cout << "Press ENTER to close the program" << std::endl;
	std::cin.get();
	return 0;
}