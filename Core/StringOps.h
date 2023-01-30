#pragma once

#include <functional>

namespace AHLib
{
	bool IsAlphabetical(const char input);

	const char* ChopString(const char* input, std::function<bool(char)> assertionFunction);
}