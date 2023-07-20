#include "Clock.h"

namespace Duck
{
	Clock::Clock()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Clock::Seconds()
	{
		return std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - m_Start).count();
	}

	long long Clock::Milliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Start).count();
	}

	void Clock::Restart()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}
}