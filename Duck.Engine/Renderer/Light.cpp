#include "Light.h"

namespace Duck
{
	Light::Light(Vector3 color, float intensity)
	{
		this->color = color;
		this->intensity = intensity;
		CalculateLight();
	}

	void Light::CalculateLight()
	{
		this->light = color * intensity;
	}

	inline const Vector3& Light::GetLight()
	{
		return light;
	}

	inline const Vector3 Light::GetColor()
	{
		return color;
	}

	inline const float Light::GetIntensity()
	{
		return intensity;
	}

	inline void Light::SetColor(const Vector3& color)
	{
		this->color = color;
		CalculateLight();
	}

	inline void Light::SetIntensity(const float& intensity)
	{
		this->intensity = intensity;
		CalculateLight();
	}
}