#pragma once
#include "Resource.h"
#include "../Graphics/Shader.h"

namespace Duck::Resources
{
	template<>
	Shader* Load<Shader>(const char* file);

	template<>
	void Unload<Shader>(const char* file);
}