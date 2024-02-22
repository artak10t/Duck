#pragma once

namespace Duck::Cosmo
{
	struct IGenerator
	{
		unsigned int seed = 0;
		virtual void Generate() = 0;
	};
}