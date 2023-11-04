#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

namespace Duck
{
	struct alignas(sizeof(Vector4) * 2) Light
	{
		Vector3 diffuse = { .35f, .35f, .35f };
		Vector3 specular = { 1.f, 1.f, 1.f };

		Light(
			Vector3 diffuse = { .35f, .35f, .35f },
			Vector3 specular = { 1.f, 1.f, 1.f });
	};
}