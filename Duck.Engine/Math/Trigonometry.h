#pragma once
#include "../pch.h"

#define PI 3.14159265358979323846264338327950288
#define RADIANS 0.01745329251994329576923690768489
#define DEGREES 57.295779513082320876798154814105
#define COS_ONE_OVER_TWO 0.877582561890372716130286068203503191

namespace Duck::Math
{
	//Radians
	template<typename T>
	inline constexpr T ToRadians(T degrees)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");

		return degrees * static_cast<T>(RADIANS);
	}

	//Degrees
	template<typename T>
	inline constexpr T ToDegrees(T radians)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'degrees' only accept floating-point input");

		return radians * static_cast<T>(DEGREES);
	}
}