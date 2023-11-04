#include "LightPoint.h"

namespace Duck
{
	LightPoint::LightPoint(
		Vector3 position, 
		Vector3 diffuse, 
		Vector3 specular, 
		float constant, 
		float linear, 
		float quadratic) 
		: Light(diffuse, specular)
	{
		this->position = position;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}
}