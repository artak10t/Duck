#pragma once
#include "Celestial.h"

namespace Duck::Cosmo
{
	class Planet : public Celestial
	{
		enum class Type
		{
			Rogue
		};

		void Solve() override;
	};
}