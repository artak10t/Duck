#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	struct Light
	{
		Vector3 diffuseColor = { .5f, .5f, .5f };
		Vector3 specularColor = { 1.f, 1.f, 1.f };

		Light(
			Vector3 diffuseColor = { .5f, .5f, .5f }, 
			Vector3 specularColor = { 1.f, 1.f, 1.f });
	};
}