#pragma once

namespace Duck::Resources
{
	inline std::string AssetsPath = "";

	void Init();

	template<typename T, typename ...Args>
	T* Load(const char* file, Args... args) { return nullptr; }

	template<typename T, typename ...Args>
	void Unload(const char* file, Args... args) { return nullptr; }
}

#include "AssetTexture.h"
#include "AssetShader.h"