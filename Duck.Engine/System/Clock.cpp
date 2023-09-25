#include "Clock.h"

namespace Duck
{
	Clock::Clock()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	float Clock::Seconds()
	{
		return std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - startTime).count();
	}

	long long Clock::Milliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
	}

	void Clock::Restart()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
}