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
		Model(const std::vector<Mesh*>& meshes);
		~Model();
		const void Draw();

	private:
		std::vector<Mesh*> m_Meshes;
	};
}