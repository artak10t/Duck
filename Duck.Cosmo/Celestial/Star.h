#pragma once
#include "../Math/ISolver.h"
#include "../Generation/IGenerator.h"

namespace Duck::Cosmo
{
	class Star : public ISolver, public IGenerator
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

			// Wormhole
			Z
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
			sd,  // Subdwarf
			D    // White Dwarf
		};

		// Parameters
		const char* name = "";
		char subtype = -1;
		SpectralType spectralType = SpectralType::Unknown;
		LuminosityClass luminosityClass = LuminosityClass::Unknown;

		unsigned int temperature = 0; // Kelvin
		float mass = -1;              // Solar Masses
		float radius = -1;            // Solar Radii
		float luminosity = -1;        // Solar Luminosity

		// Methods
		void Solve() override;
		void Generate() override;
	};
}