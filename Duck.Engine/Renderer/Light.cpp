#include "Light.h"

namespace Duck
{
	Light::Light(Vector3 diffuse, Vector3 specular)
	{
		this->diffuse = diffuse;
		this->specular = specular;
	}
}