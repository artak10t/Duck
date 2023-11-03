#pragma once
#include "Light.h"

#include "../Math/Vector3.h"

namespace Duck 
{
	struct LightDirectional : public Light
	{
		Vector3 direction = { 1.f, 0.f, 0.f };

		LightDirectional(
			Vector3 direction = { 1.f, 0.f, 1.f }, 
			Vector3 diffuseColor = { .5f, .5f, .5f }, 
			Vector3 specularColor = { 1.f, 1.f, 1.f });
	};
}