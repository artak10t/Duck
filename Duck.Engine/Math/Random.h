#pragma once

namespace Duck::Random
{
	inline constexpr float Range(float a, float b)
	{
		return 0;
	}	

	inline constexpr int Range(int a, int b)
	{
		return 0;
	}

	template<typename T>
	inline constexpr float Range(T a, T b)
	{
		return Range(static_cast<float>(a), static_cast<float>(b));
	}
}