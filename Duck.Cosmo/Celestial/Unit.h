#pragma once

namespace Duck::Cosmo
{
	struct Mass
	{
		enum Unit
		{
			Kilogram,
			Tonne,
			Lunar,
			Earth,
			Jupiter,
			Solar
		};

		static const char* Symbol(const Unit unit = DEFAULT_UNIT_MASS);
		static void Convert(double& value, Unit from, Unit to);

		double Get(const Unit unit = DEFAULT_UNIT_MASS);
		void Set(double value, const Unit unit = DEFAULT_UNIT_MASS);

	private:
		const static Unit DEFAULT_UNIT_MASS = Earth;
		double value = 0;
	};
}