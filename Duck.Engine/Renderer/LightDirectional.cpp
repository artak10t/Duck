#include "LightDirectional.h"

namespace Duck
{
	LightDirectional::LightDirectional(
		Vector3 direction, 
		Vector3 diffuse, 
		Vector3 specular) 
		: Light(diffuse, specular)
	{
		this->direction = direction;
	}
}