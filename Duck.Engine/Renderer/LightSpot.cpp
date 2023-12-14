#include "LightSpot.h"
#include "Renderer.h"

namespace Duck
{
	std::vector<LightSpot*> Renderer::spotLights;

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

		index = Renderer::spotLights.size();
		Renderer::spotLights.push_back(this);
	}

	LightSpot::~LightSpot()
	{
		if (index < Renderer::spotLights.size())
		{
			Renderer::spotLights.erase(Renderer::spotLights.begin() + index);
		}
	}
}