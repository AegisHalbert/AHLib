#pragma once

#include <chrono>
#include <iostream>

namespace ahl
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