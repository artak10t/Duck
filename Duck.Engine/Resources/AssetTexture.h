#pragma once
#include "Resources.h"
#include "../Graphics/Texture.h"

namespace Duck::Resources
{
	template<>
	Texture* Load<Texture>(const char* file);

	template<>
	Texture* Load<Texture>(const char* file, const Texture::Filter filtering, const Texture::Wrap wrapping);

	template<>
	void Unload<Texture>(const char* file);
}