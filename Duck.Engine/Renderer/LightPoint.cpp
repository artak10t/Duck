#include "LightPoint.h"

namespace Duck
{
	LightPoint::LightPoint(
		Vector3 position, 
		Vector3 diffuseColor, 
		Vector3 specularColor, 
		float constant, 
		float linear, 
		float quadratic) 
		: Light(diffuseColor, specularColor)
	{
		this->position = position;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}
}