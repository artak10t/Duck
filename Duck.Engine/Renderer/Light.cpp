#include "Light.h"

namespace Duck
{
	Light::Light(Vector3 diffuseColor, Vector3 specularColor)
	{
		this->diffuseColor = diffuseColor;
		this->specularColor = specularColor;
	}

	inline const Vector3& Light::GetDiffuseColor()
	{
		return diffuseColor;
	}

	inline void Light::SetDiffuseColor(const Vector3& color)
	{
		this->diffuseColor = color;
	}

	inline const Vector3& Light::GetSpecularColor()
	{
		return specularColor;
	}

	inline void Light::SetSpecularColor(const Vector3& color)
	{
		this->specularColor = color;
	}
}