#pragma once
#include "Light.h"

#include "../Math/Vector3.h"

namespace Duck
{
	struct LightPoint : public Light
	{
		Vector3 position = { 0.f, 0.f, 0.f };
		float constant = 1.f;
		float linear = .09f;
		float quadratic = .032f;

		LightPoint(
			Vector3 position = { 1.f, 0.f, 1.f }, 
			Vector3 diffuseColor = { .5f, .5f, .5f }, 
			Vector3 specularColor = { 1.f, 1.f, 1.f },
			float constant = 1.f,
			float linear = .09f,
			float quadratic = .032f);
	};
}