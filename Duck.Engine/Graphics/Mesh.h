#pragma once
#include "../pch.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

namespace Duck
{
	struct Vertex final
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
	};

	class Mesh final
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		const void Draw();

	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		int indicesCount = 0;

		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ebo = 0;
	};
}