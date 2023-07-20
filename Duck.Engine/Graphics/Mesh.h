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
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
	};
}