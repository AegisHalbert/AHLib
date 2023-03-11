#include <Meta/Benchmark.h>

namespace ahl
{
	void ScopeWatch::StartWatch()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	ScopeWatch::ScopeWatch(const char* name) : m_name(name)
	{
		StartWatch();
	}
	ScopeWatch::~ScopeWatch()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();

		int startms = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
		int endms = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		std::cout << "ScopeWatch-" << m_name << ": " << (endms - startms) << "ms" << std::endl;
	} 
}