#pragma once
#include "Camera.h"

namespace Duck
{
	class CameraOrthographic final : public Camera
	{
	public:
		CameraOrthographic(const float& near = -100.f, const float& far = 100.f);
		virtual void RecalculateProjectionMatrix() override;
	};
}