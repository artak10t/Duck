#pragma once
#include "../pch.h"

namespace Duck
{
	class Clock final
	{
	public:
		Clock();
		float Seconds();
		long long Milliseconds();
		void Restart();

	private:
		std::chrono::steady_clock::time_point start;
	};
}