#include "LightDirectional.h"

namespace Duck
{
	LightDirectional::LightDirectional(
		Vector3 direction, 
		Vector3 diffuseColor, 
		Vector3 specularColor) 
		: Light(diffuseColor, specularColor)
	{
		this->direction = direction;
	}
}