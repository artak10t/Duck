#include "Mesh.h"
#include <glad/glad.h>

namespace Duck
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		this->vertices = vertices;
		this->indices = indices;
		indicesCount = static_cast<int>(indices.size());

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		// Bind VAO
		glBindVertexArray(vao);

		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// Bind Position vertex attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Bind Normal vertex attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// Bind UV vertex attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO
		glBindVertexArray(0);

		// Unbind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	const void Mesh::Draw()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}