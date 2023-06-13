#pragma once
#include <cstdlib>

namespace Duck::Random
{
	// Set seed of random values
	inline void SetSeed(const unsigned int& seed)
	{
		std::srand(seed);
	}

	// Random value between [min, max] inclusive
	template<typename T>
	inline T Range(const T& min, const T& max)
	{
		return min + static_cast<T>(std::rand()) / (static_cast<T>(RAND_MAX / (max - min + 1)));
	}
}