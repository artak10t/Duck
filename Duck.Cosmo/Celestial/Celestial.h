#pragma once
#include "Unit.h"

namespace Duck::Cosmo
{
	class Celestial
	{
	public:
		virtual void Solve() = 0;

	public:
		Mass mass;

	protected:
		const char* name = "";
	};
}