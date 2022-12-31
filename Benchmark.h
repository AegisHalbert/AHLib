#pragma once
#ifdef _DEBUG

#include <chrono>

namespace AHLib
{
	class ScopeWatch
	{
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	public:
		ScopeWatch(const char* name);
		~ScopeWatch();
	private:
		void StartWatch();
	};
}

#endif 