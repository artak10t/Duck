#pragma once
#include "Light.h"

#include "../Math/Vector3.h"

namespace Duck
{
	struct LightSpot : public Light
	{
		Vector3 position = { 0.f, 0.f, 0.f };
		Vector3 direction = { 1.f, 0.f, 0.f };
		float cutoff = .976f;

		LightSpot(
			Vector3 position = { 1.f, 0.f, 1.f },
			Vector3 direction = { 1.f, 0.f, 0.f },
			Vector3 diffuse = { .35f, .35f, .35f },
			Vector3 specular = { 1.f, 1.f, 1.f },
			float cutoff = .976f);
	};
}