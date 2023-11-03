#include "Light.h"

namespace Duck
{
	Light::Light(Vector3 diffuseColor, Vector3 specularColor)
	{
		this->diffuseColor = diffuseColor;
		this->specularColor = specularColor;
	}
}