#include "Clock.h"

namespace Duck
{
	Clock::Clock()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	float Clock::Seconds()
	{
		return std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - start).count();
	}

	long long Clock::Milliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	}

	void Clock::Restart()
	{
		start = std::chrono::high_resolution_clock::now();
	}
}