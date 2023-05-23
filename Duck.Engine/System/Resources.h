#pragma once
#include "../Graphics/Texture.h"
#include "../Graphics/Shader.h"

namespace Duck::Resources
{
	template<typename T, typename ...Args>
	T* Load(const char* file, Args... args);
	template<typename T, typename ...Args>
	void Unload(const char* file, Args... args);

	void Init();
	void Clear();

	//Texture supports 3 and 4 channel textures
	template<>
	Texture* Load<Texture>(const char* file);
	//FIX: Pass by reference
	template<>
	Texture* Load<Texture>(const char* file, const Texture::FilterMode filtering, const Texture::WrapMode wrapping);
	template<>
	void Unload<Texture>(const char* file);

	//Shader loads and compiles requires .shader
	template<>
	Shader* Load<Shader>(const char* file);
	template<>
	void Unload<Shader>(const char* file);
}