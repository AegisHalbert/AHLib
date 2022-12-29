#ifdef _DEBUG

#include <iostream>

#include "Benchmark.h"

namespace AHLib
{
	class ScopeWatch
	{
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	public:
		ScopeWatch() : m_name("\155")
		{
			startTime = std::chrono::high_resolution_clock::now();
		}
		ScopeWatch(const char* name) : m_name(name)
		{
			ScopeWatch();
		}
		~ScopeWatch()
		{
			std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();

			float startms = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
			float endms = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

			std::cout << "ScopeWatch-" << m_name << ": " << (endms - startms) << "ms" << std::endl;
		}
	};
}

#endif 