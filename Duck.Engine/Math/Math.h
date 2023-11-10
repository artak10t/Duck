#pragma once
#include "../pch.h"

namespace Duck::Math
{
	// Radians
	template<typename T>
	inline constexpr T Clamp(T value, T min, T max)
	{
		return std::clamp(value, min, max);
	}
}