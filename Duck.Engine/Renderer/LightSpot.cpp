#include "LightSpot.h"

namespace Duck
{
	LightSpot::LightSpot(
		Vector3 position, 
		Vector3 direction, 
		Vector3 diffuse, 
		Vector3 specular, 
		float cutoff) 
		: Light(diffuse, specular)
	{
		this->position = position;
		this->direction = direction;
		this->cutoff = cutoff;
	}
}