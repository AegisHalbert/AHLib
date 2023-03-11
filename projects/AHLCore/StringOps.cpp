#include <Core/StringOps.h>

namespace ahl
{
	bool IsAlphabetical(const char input)
	{
		return (input > 64 && input < 91) || (input > 96 && input < 123);
	};

	const char* ChopString(const char* input, std::function<bool(char)> assertionFunction)
	{
		int inputLength = strlen(input);
		char* newString = new char[inputLength + 1];

		char selectedChar;
		int constructingIndex = 0;
		for (int i = 0; i < inputLength; i++)
		{
			selectedChar = input[i];
			if (assertionFunction(selectedChar))
			{
				newString[constructingIndex] = selectedChar;
				constructingIndex++;
			}
		}

		newString[constructingIndex] = 0;

		return newString;
	}
}