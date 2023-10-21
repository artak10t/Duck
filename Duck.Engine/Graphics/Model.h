#pragma once
#include "../pch.h"

#include "Mesh.h"
#include "Texture.h"

// Supports gltf models only
namespace Duck 
{
	class Model final
	{
	public:
		std::vector<Mesh*> meshes;
		std::vector<Texture*> textures;

		Model(std::string_view file);
		~Model();
		const void Draw();
	};
}