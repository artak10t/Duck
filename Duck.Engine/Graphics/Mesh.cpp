#include "Mesh.h"
#include <glad/glad.h>

namespace Duck
{
	Mesh::Mesh() : Mesh(std::vector<Vector3> {}, std::vector<Vector3> {}, std::vector<Vector2> {}, std::vector<unsigned int> {}) {}

	Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<unsigned int>& triangles) : Mesh(vertices, std::vector<Vector3> {}, std::vector<Vector2> {}, triangles) {}

	Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector2>& uv, const std::vector<unsigned int>& triangles) : Mesh(vertices, std::vector<Vector3> {}, uv, triangles) {}

	Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::vector<unsigned int>& triangles) : Mesh(vertices, normals, std::vector<Vector2>{}, triangles) {}

	Mesh::Mesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::vector<Vector2>& uv, const std::vector<unsigned int>& triangles)
	{
		this->vertices = vertices;
		this->normals = normals;
		this->uv = uv;
		this->triangles = triangles;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		UploadData();

		// Bind VAO
		glBindVertexArray(VAO);

		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		size_t vertices_size = vertices.size() * sizeof(Vector3);
		size_t normals_size = normals.size() * sizeof(Vector3);

		// Bind Position Attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);

		// Bind Normal Attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)(vertices_size));

		// Bind UV Attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)(vertices_size + normals_size));

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO
		glBindVertexArray(0);

		// Unbind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
	
	const void Mesh::UploadData()
	{
		// Bind VAO
		glBindVertexArray(VAO);

		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		size_t vertices_size = vertices.size() * sizeof(Vector3);
		size_t normals_size = normals.size() * sizeof(Vector3);
		size_t uv_size = uv.size() * sizeof(Vector2);

		int current_allocated_size = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &current_allocated_size);

		if((vertices_size + normals_size + uv_size) != current_allocated_size)
			glBufferData(GL_ARRAY_BUFFER, vertices_size + normals_size + uv_size, nullptr, GL_STATIC_DRAW);

		if (vertices_size != 0)
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, &vertices[0]);

		if (normals_size != 0)
			glBufferSubData(GL_ARRAY_BUFFER, vertices_size, normals_size, &normals[0]);

		if (uv_size != 0)
			glBufferSubData(GL_ARRAY_BUFFER, vertices_size + normals_size, uv_size, &uv[0]);

		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		if (triangles.size() != 0)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->triangles.size() * sizeof(unsigned int), &this->triangles[0], GL_STATIC_DRAW);

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO
		glBindVertexArray(0);

		// Unbind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	const void Mesh::Draw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, GLsizei(triangles.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}