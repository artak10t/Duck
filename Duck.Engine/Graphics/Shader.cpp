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
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			Logger::Error("Shader - Vertex failed to compile\n%s\n", infoLog);
		}

		// Fragment Shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragment, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			Logger::Error("Shader - Fragment failed to compile\n%s\n", infoLog);
		}

		// Shader Program
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) 
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			Logger::Error("Shader - Program failed to link\n%s\n", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Bind Camera UBO
		unsigned int uniformBlockCamera = glGetUniformBlockIndex(program, "CameraUBO");
		glUniformBlockBinding(program, uniformBlockCamera, 0);

		// Bind Lighting UBO
		unsigned int uniformBlockLighting = glGetUniformBlockIndex(program, "LightingUBO");
		glUniformBlockBinding(program, uniformBlockLighting, 1);
	}

	Shader::~Shader()
	{
		glDeleteProgram(program);
	}

	void Shader::Bind()
	{
		glUseProgram(program);
	}

	//Uniforms
	void Shader::SetInt(const char* name, const int& i)
	{
		Bind();
		glUniform1i(getUniformLocation(name), i);
	}

	void Shader::SetFloat(const char* name, const float& f)
	{
		Bind();
		glUniform1f(getUniformLocation(name), f);
	}
	
	void Shader::SetVector2(const char* name, const Vector2& v)
	{
		Bind();
		glUniform2f(getUniformLocation(name), v.x, v.y);
	}

	void Shader::SetVector3(const char* name, const Vector3& v)
	{
		Bind();
		glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
	}

	void Shader::SetVector4(const char* name, const Vector4& v)
	{
		Bind();
		glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void Shader::SetMatrix4(const char* name, const Matrix4& m)
	{
		Bind();
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
	}

	//Caching Uniforms
	int Shader::getUniformLocation(const char* name) const
	{
		if (cachedUniforms.find(name) != cachedUniforms.end())
			return cachedUniforms[name];

		int l = glGetUniformLocation(program, name);
		if (l == -1)
		{
			Logger::Error("Shader - '%s' Matrix4 Uniform doesn't exist", name);
			return -1;
		}

		cachedUniforms[name] = l;
		return l;
	}
}