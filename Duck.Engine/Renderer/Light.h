#pragma once
#include "../Math/Vector3.h"

namespace Duck
{
	class Light
	{
	protected:
		Vector3 light = { 0, 0, 0 };
		Vector3 color = { 1.f, 1.f, 1.f };
		float intensity = .5f;

		virtual void CalculateLight();

	public:
		Light(Vector3 color = { 1.f, 1.f, 1.f }, float intensity = .5f);

		virtual inline const Vector3& GetLight();
		virtual inline const Vector3 GetColor();
		virtual inline const float GetIntensity();
		virtual inline void SetColor(const Vector3& color);
		virtual inline void SetIntensity(const float& intensity);
	};
}