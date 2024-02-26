#pragma once
#include "Resource.h"
#include "../Renderer/Shader.h"

namespace Duck::Resources
{
	template<>
	Shader* Load<Shader>(const char* file);

	template<>
	void Unload<Shader>(const char* file);
}