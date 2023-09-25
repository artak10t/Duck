#pragma once
#include "../pch.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

namespace Duck
{
	class Mesh final
	{
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> uv;
		std::vector<unsigned int> triangles;

		Mesh();
		Mesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& triangles);
		Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector2>& uv, const std::vector<unsigned int>& triangles);
		Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::vector<unsigned int>& triangles);
		Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::vector<Vector2>& uv, const std::vector<unsigned int>& triangles);
		~Mesh();
		const void UploadData();
		const void Draw();

	private:
		unsigned int VAO = 0;
		unsigned int VBO = 0;
		unsigned int EBO = 0;
	};
}