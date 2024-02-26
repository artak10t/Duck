#pragma once
#include "Resource.h"
#include "../Renderer/Model.h"

namespace Duck::Resources
{
	template<>
	Model* Load<Model>(const char* file);

	template<>
	void Unload<Model>(const char* file);
}