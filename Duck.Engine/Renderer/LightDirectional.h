#pragma once
#include "Light.h"

#include "../Math/Vector3.h"

namespace Duck 
{
	struct alignas(sizeof(Light) * 2) LightDirectional : public Light
	{
		Vector3 direction = { 1.f, -.5f, .5f };

		LightDirectional(
			Vector3 direction = { 1.f, -.5f, .5f },
			Vector3 diffuse = { .5f, .5f, .5f }, 
			Vector3 specular = { 1.f, 1.f, 1.f });
	};
}