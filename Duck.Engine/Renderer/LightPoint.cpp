#include "LightPoint.h"
#include "Renderer.h"

namespace Duck
{
	std::vector<LightPoint*> Renderer::pointLights;

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

		index = Renderer::pointLights.size();
		Renderer::pointLights.push_back(this);
	}

	LightPoint::~LightPoint()
	{
		if (index < Renderer::pointLights.size())
		{
			Renderer::pointLights.erase(Renderer::pointLights.begin() + index);
		}
	}
}