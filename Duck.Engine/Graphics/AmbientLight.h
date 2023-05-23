#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	struct AmbientLight
	{
	private:
		Vector3 _light = Vector3(1.f);
		Vector3 _color = Vector3(1.f);
		float _intensity = 1.f;

	public:
		AmbientLight()
		{
			_light = _color * _intensity;
		}

		inline const Vector3& GetColor()
		{
			return _color;
		}

		inline const float GetIntensity()
		{
			return _intensity;
		}

		inline void SetColor(const Vector3& color)
		{
			_color = color;
			_light = _color * _intensity;
		}

		inline void SetIntensity(const float& intensity)
		{
			_intensity = intensity;
			_light = _color * _intensity;
		}

		inline const Vector3& GetLight()
		{
			return _light;
		}
	};
}