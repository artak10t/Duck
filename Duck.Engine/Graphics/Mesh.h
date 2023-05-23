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
		Vector3 color;
		Vector2 uv;
	};

	class Mesh final
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		void Draw();

	private:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		int _indicesCount = 0;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;
	};
}