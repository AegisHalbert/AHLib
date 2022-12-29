#pragma once
#ifdef _DEBUG

#include <chrono>

namespace AHLib
{
	class ScopeWatch
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	public:
		ScopeWatch();
		ScopeWatch(const char* name);

		~ScopeWatch();
	};
}

#endif 