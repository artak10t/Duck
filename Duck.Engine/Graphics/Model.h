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
		Model(const char* path);
		~Model();
		const void Draw();

	private:
		std::vector<Mesh*> _meshes;
		std::vector<Texture*> _textures;
	};
}