#include <iostream>
#include <filesystem>
#include <string>

#include <fstream>

#include <vector>

static const std::string CONFIGFILENAME = "config.txt";
static const std::string VERSIOFILENAME = "version.txt";

static const char SEPARATOR = std::filesystem::path::preferred_separator;

static std::vector<std::string> extensionsList;

std::ostream& operator<<(std::ostream& stream, const std::filesystem::file_time_type time)
{
	stream << time.time_since_epoch().count();
	return stream;
}

static void PrintPathContent(std::filesystem::directory_entry workingDirectory, bool recursive = false)
{
	std::cout << "-----PATH-CONTENT-----" << std::endl;

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

static bool ConfigurationExists(std::filesystem::directory_entry workingDirectory)
{
	std::filesystem::directory_iterator directoryIterate(workingDirectory);

	bool configFound = false;
	for (std::filesystem::directory_entry entry : directoryIterate)
	{
		if (entry.path().filename() == CONFIGFILENAME)
		{
			configFound = true;
			break;
		}
	}

	return configFound;
}

static bool VersionFileExists(std::filesystem::directory_entry workingDirectory)
{
	std::filesystem::directory_iterator directoryIterate(workingDirectory);

	bool versionFound = false;
	for (std::filesystem::directory_entry entry : directoryIterate)
	{
		if (entry.path().filename() == VERSIOFILENAME)
		{
			versionFound = true;
			break;
		}
	}

	return versionFound;
}

static int lastExtensionIndex = 0;

static void GetTrackedExtensions(char* buffer, int fileLength)
{
	bool extensionsRead = false;

	for (int i = 0; i < fileLength; i++)
	{
		char& selectedChar = buffer[i];
		if (!extensionsRead)
		{
			if (selectedChar == '\n')
			{
				extensionsRead = true;

				int newExtensionLength = (i - lastExtensionIndex);
				char* newExtension = new char[newExtensionLength];
				for (int j = 0; j < newExtensionLength; j++)
				{
					newExtension[j] = buffer[j + lastExtensionIndex + 1];
				}
				newExtension[newExtensionLength - 1] = 0;

				std::string extensionString(newExtension);
				extensionsList.emplace_back(extensionString);

				lastExtensionIndex = i + 1;
			}

			if (selectedChar == ' ')
			{
				int newExtensionLength = (i - lastExtensionIndex);
				char* newExtension = new char[newExtensionLength];

				for (int j = 0; j < newExtensionLength; j++)
				{
					newExtension[j] = buffer[j + lastExtensionIndex + 1];
				}
				newExtension[newExtensionLength - 1] = 0;

				std::string extensionString(newExtension);
				extensionsList.emplace_back(extensionString);

				lastExtensionIndex = i + 1;
			}
		}
		else break;
	}
}

std::vector<std::string> ignoredFiles;

static void GetIgnoredFiles(char* buffer, int fileLength)
{
	int linesSkipped = 0;
	int lastLineOffset = 0;

	int lineSkipTimes = 0;
	int constructTimes = 0;

	for (int i = 0; i < fileLength; i++)
	{
		char& selectedChar = buffer[i];

		if (selectedChar == '\n')
		{
			if (linesSkipped < 2)
			{
				linesSkipped++;
				lastLineOffset = i;
			}
				
			else
			{
				int newExtensionLength = (i - lastLineOffset);
				char* newFilePath = new char[newExtensionLength];

				for (int j = 0; j < newExtensionLength; j++)
				{
					newFilePath[j] = buffer[j + lastLineOffset + 1];
				}
				newFilePath[newExtensionLength - 1] = 0;

				std::string newFilePathName(newFilePath);
				ignoredFiles.emplace_back(newFilePathName);

				lastLineOffset = i;
			}
		}
	}
}

int main()
{
	std::filesystem::path workingPath = std::filesystem::current_path();

	std::cout << "BOOT AT: ";
	std::cout << workingPath << std::endl;
	std::cout << "---------------------- " << std::endl;

	std::filesystem::directory_entry workingDirectory(workingPath);

	bool configurationExists = ConfigurationExists(workingDirectory);

	std::string configPath = workingPath.string() + SEPARATOR + CONFIGFILENAME;
	if (!configurationExists)
	{
		std::cout << "Configuration doesn't exists. Creating config.txt" << std::endl;

		std::ofstream newFile(configPath.c_str());

		std::string fullCommand = "";
		std::string command = "";
		std::string parameter = "";

		int whiteSpaceAt = 0;

		std::vector<std::string> acceptedExtensions;
		while (command != "stop")
		{
			std::cout << std::endl;
			std::cout << "add [extension] : [extension] is added to the list that will be tracked. Don't add the dot." << std::endl;
			std::cout << "stop            : stop adding extensions and finish writing the config file" << std::endl;

			std::getline(std::cin, fullCommand);
			
			if (fullCommand == "stop")
			{
				command = "stop";
				continue;
			}

			whiteSpaceAt = fullCommand.find(' ');
			if (whiteSpaceAt == fullCommand.npos)
			{
				std::cout << "ERROR command, try again. No space (?)" << std::endl;
				continue;
			}

			command = fullCommand.substr(0, whiteSpaceAt);
			parameter = fullCommand.substr(whiteSpaceAt + 1);

			if (command == "add")
			{
				std::cout << "Extension added correctly" << std::endl;
				acceptedExtensions.push_back("." + parameter + " ");
			}
			else
			{
				if (command != "stop")
				{
					std::cout << "ERROR command, try again. No recognized (?)" << std::endl;
					continue;
				}
			}
		}

		for (int i = 0; i < acceptedExtensions.size(); i++)
		{
			newFile << acceptedExtensions[i];
		}
		newFile << std::endl;

		newFile << "---Files ignored. Defaults to all the files found on root upon config.txt creation.---" << std::endl;

		std::filesystem::directory_iterator directoryIterate(workingDirectory);
		for (std::filesystem::directory_entry entry : directoryIterate)
		{
			newFile << entry.path().filename() << std::endl;
		}

		newFile.flush();
		newFile.close();

		std::cout << "Configuration file created " << std::endl;
	}
	else
	{
		std::cout << "Configuration file found " << std::endl;

		std::ifstream configFile(configPath.c_str(), std::ifstream::binary);

		configFile.seekg(0, configFile.end);
		int fileLength = configFile.tellg();
		configFile.seekg(0, configFile.beg);

		char* buffer = new char[fileLength];

		configFile.read(buffer, fileLength);
		configFile.close();

		GetTrackedExtensions(buffer, fileLength);

		std::cout << "Tracking extensions: ";
		for (int i = 0; i < extensionsList.size(); i++)
		{
			std::cout << extensionsList[i] << " ";
		}
		std::cout << std::endl;

		GetIgnoredFiles(buffer, fileLength);

		std::cout << "Files ignored: " << std::endl;
		for (int i = 0; i < ignoredFiles.size(); i++)
		{
			std::cout << ignoredFiles[i] << std::endl;
		}
		std::cout << std::endl;

		delete[] buffer;

	}

	std::string versionPath = workingPath.string() + SEPARATOR + CONFIGFILENAME;
	if (!VersionFileExists(workingDirectory))
	{
		std::cout << "Version file doesn't exists. Creating version.txt" << std::endl;
		std::cout << "First version needs to be created to create the file." << std::endl;
	}
	else
	{

	}

	std::cout << std::endl;
	std::cout << "Press ENTER to close the program" << std::endl;
	std::cin.get();
	return 0;
}