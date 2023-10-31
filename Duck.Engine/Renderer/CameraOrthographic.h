#pragma once
#include "Camera.h"

namespace Duck
{
	class CameraOrthographic final : public Camera
	{
	public:
		CameraOrthographic(const float& near = -250.f, const float& far = 250.f);
		virtual void RecalculateProjectionMatrix() override;
	};
}