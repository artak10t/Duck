#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	class Light
	{
	protected:
		Vector3 light = { 0, 0, 0 };
		Vector3 diffuseColor = { .5f, .5f, .5f };
		Vector3 specularColor = { 1.f, 1.f, 1.f };

	public:
		Light(Vector3 diffuseColor = { .5f, .5f, .5f }, Vector3 specularColor = { 1.f, 1.f, 1.f });

		virtual inline const Vector3& GetDiffuseColor();
		virtual inline void SetDiffuseColor(const Vector3& color);
		virtual inline const Vector3& GetSpecularColor();
		virtual inline void SetSpecularColor(const Vector3& color);
	};
}