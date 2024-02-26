#include "Unit.h"

#include <stdexcept>

namespace Duck::Cosmo
{
	const char* Mass::Symbol(const Unit unit)
	{
		const char* symbol = "";
		
		switch (unit)
		{
		case Kilogram:
			symbol = "kg";
			break;
		case Tonne:
			symbol = "t";
			break;
		case Lunar:
			symbol = "Ml";
			break;
		case Earth:
			symbol = "Me";
			break;
		case Jupiter:
			symbol = "Mj";
			break;
		case Solar:
			symbol = "Ms";
			break;
		}

		return symbol;
	}

	void Mass::Convert(double& value, Unit from, Unit to)
	{
		switch (from)
		{
		case Kilogram:
			switch (to)
			{
			case Tonne:
				value *= 0.001;
				break;
			case Lunar:
				value *= 1.3613e-23;
				break;
			case Earth:
				value *= 1.6744e-25;
				break;
			case Jupiter:
				value *= 5.2682e-28;
				break;
			case Solar:
				value *= 5.0290e-31;
				break;
			}
			break;
		case Tonne:
			switch (to)
			{
			case Kilogram:
				value *= 1000;
			case Lunar:
				value *= 1.3613e-20;
				break;
			case Earth:
				value *= 1.6744e-22;
				break;
			case Jupiter:
				value *= 5.2682e-25;
				break;
			case Solar:
				value *= 5.0290e-28;
				break;
			}
			break;
		case Lunar:
			switch (to)
			{
			case Kilogram:
				value *= 7.346e22;
				break;
			case Tonne:
				value *= 7.346e19;
				break;
			case Earth:
				value *= 0.0123;
				break;
			case Jupiter:
				value *= 0.0000387;
				break;
			case Solar:
				value *= 0.00000003694;
				break;
			}
			break;
		case Earth:
			switch (to)
			{
			case Kilogram:
				value *= 5.9724e24;
				break;
			case Tonne:
				value *= 5.9724e21;
				break;
			case Lunar:
				value *= 81.3014;
				break;
			case Jupiter:
				value *= 0.003146;
				break;
			case Solar:
				value *= 0.000003004;
				break;
			}
			break;
		case Jupiter:
			switch (to)
			{
			case Kilogram:
				value *= 1.8982e27;
				break;
			case Tonne:
				value *= 1.8982e24;
				break;
			case Lunar:
				value *= 25839.7767;
				break;
			case Earth:
				value *= 317.827;
				break;
			case Solar:
				value *= 0.0009546;
				break;
			}
			break;
		case Solar:
			switch (to)
			{
			case Kilogram:
				value *= 1.9885e30;
				break;
			case Tonne:
				value *= 1.9885e27;
				break;
			case Lunar:
				value *= 27068744.8952;
				break;
			case Earth:
				value *= 332943.2054;
				break;
			case Jupiter:
				value *= 1047.5611;
				break;
			}
			break;
		}
	}

	double Mass::Get(const Unit unit)
	{
		if (unit == DEFAULT_UNIT_MASS)
			return this->value;

		double value = this->value;

		Convert(value, DEFAULT_UNIT_MASS, unit);

		return value;
	}

	void Mass::Set(double value, const Unit unit)
	{
		if (this->value < 0)
			throw std::invalid_argument("Mass can't be negative");

		if (unit == DEFAULT_UNIT_MASS)
		{
			this->value = value;
			return;
		}

		Convert(value, unit, DEFAULT_UNIT_MASS);

		this->value = value;
	}
}