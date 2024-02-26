#pragma once
#include "Celestial.h"

namespace Duck::Cosmo
{
	class Star : public Celestial
	{
	public:
		enum class SpectralType
		{
			Unknown,

			// Normal
			O,
			B,
			A,
			F,
			G,
			K,
			M,

			// Brown Dwarf
			L,
			T,
			Y,

			// Wolf-Rayet
			WN,
			WNC,
			WC,
			WO,

			// Carbon
			MS,
			S,
			SC,
			CR,
			CN,
			CJ,
			CH,
			CHd,
			C,
			R,
			N,

			// Neutron
			Q,

			// Black Hole
			X,
		};

		enum class LuminosityClass
		{
			Unknown,

			Ia0, // Hypergiant
			Ia,  // Luminous Supergiant
			Iab, // Intermediate Supergiant
			Ib,  // Less Luminous Supergiant
			II,  // Bright Giant
			III, // Giant
			IV,  // Subgiant
			V,   // Main-Sequence
			Sd,  // Subdwarf
			D    // White Dwarf
		};

	private:
		char subtype = -1;
		SpectralType spectralType = SpectralType::Unknown;
		LuminosityClass luminosityClass = LuminosityClass::Unknown;

		void Solve() override;
	};
}