#pragma once
#include "Camera.h"

namespace Duck
{
	class CameraOrthographic final : public Camera
	{
	public:
		CameraOrthographic(const float& zNear = -100.f, const float& zFar = 100.f);
		virtual void RecalculateProjectionMatrix() override;
	};
}