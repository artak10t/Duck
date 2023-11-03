#include "LightSpot.h"

namespace Duck
{
	LightSpot::LightSpot(
		Vector3 position, 
		Vector3 direction, 
		Vector3 diffuseColor, 
		Vector3 specularColor, 
		float cutoff) 
		: Light(diffuseColor, specularColor)
	{
		this->position = position;
		this->direction = direction;
		this->cutoff = cutoff;
	}
}