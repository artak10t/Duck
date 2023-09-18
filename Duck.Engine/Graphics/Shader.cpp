#include "Shader.h"
#include <glad/glad.h>

#include "../System/Logger.h"

namespace Duck
{
	Shader::Shader(const char* vertex, const char* fragment)
	{
		// Vertex Shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertex, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		DUCK_ASSERT(success, "Shader - Vertex failed to compile\n%s\n", infoLog)

		// Fragment Shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragment, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		DUCK_ASSERT(success, "Shader - Fragment failed to compile\n%s\n", infoLog)

		// Shader Program
		m_Program = glCreateProgram();
		glAttachShader(m_Program, vertexShader);
		glAttachShader(m_Program, fragmentShader);
		glLinkProgram(m_Program);

		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
		DUCK_ASSERT(success, "Shader - Program failed to link\n%s\n", infoLog)

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Bind Camera UBO
		unsigned int uniformBlockCamera = glGetUniformBlockIndex(m_Program, "CameraUBO");
		glUniformBlockBinding(m_Program, uniformBlockCamera, 0);

		// Bind Lighting UBO
		unsigned int uniformBlockLighting = glGetUniformBlockIndex(m_Program, "LightingUBO");
		glUniformBlockBinding(m_Program, uniformBlockLighting, 1);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	//Uniforms
	void Shader::SetInt(const char* name, const int& i)
	{
		Bind();
		glUniform1i(GetUniformLocation(name), i);
	}

	void Shader::SetFloat(const char* name, const float& f)
	{
		Bind();
		glUniform1f(GetUniformLocation(name), f);
	}
	
	void Shader::SetVector2(const char* name, const Vector2& v)
	{
		Bind();
		glUniform2f(GetUniformLocation(name), v.x, v.y);
	}

	void Shader::SetVector3(const char* name, const Vector3& v)
	{
		Bind();
		glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
	}

	void Shader::SetVector4(const char* name, const Vector4& v)
	{
		Bind();
		glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void Shader::SetMatrix4(const char* name, const Matrix4& m)
	{
		Bind();
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m[0][0]);
	}

	//Caching Uniforms
	int Shader::GetUniformLocation(const char* name) const
	{
		if (m_Cache.find(name) != m_Cache.end())
			return m_Cache[name];

		int l = glGetUniformLocation(m_Program, name);
		if (l == -1)
		{
			Logger::Error("Shader - '%s' Matrix4 Uniform doesn't exist", name);
			return -1;
		}

		m_Cache[name] = l;
		return l;
	}
}