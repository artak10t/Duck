#pragma once
#include "../pch.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4.h"

namespace Duck 
{
	class Shader final
	{
	public:
		Shader(const char* vertex, const char* fragment);
		~Shader();
		void Bind();

		//Uniforms
		void SetInt(const char* name, const int& i);
		void SetFloat(const char* name, const float& f);
		void SetVector2(const char* name, const Vector2& v);
		void SetVector3(const char* name, const Vector3& v);
		void SetVector4(const char* name, const Vector4& v);
		void SetMatrix4(const char* name, const Matrix4& m);

	private:
		unsigned int m_Program = 0;
		mutable std::unordered_map<const char*, int> m_Cache;

		int GetUniformLocation(const char* name) const;
	};
}