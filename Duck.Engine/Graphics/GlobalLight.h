#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	struct GlobalLight
	{
	private:
		Vector3 light = Vector3(1.f);
		Vector3 color = Vector3(1.f);
		float intensity = .5f;

	public:
		GlobalLight()
		{
			light = color * intensity;
		}

		inline const Vector3& GetColor()
		{
			return color;
		}

		inline const float GetIntensity()
		{
			return intensity;
		}

		inline void SetColor(const Vector3& color)
		{
			this->color = color;
			light = color * intensity;
		}

		inline void SetIntensity(const float& intensity)
		{
			this->intensity = intensity;
			light = color * intensity;
		}

		inline const Vector3& GetLight()
		{
			return light;
		}
	};
}