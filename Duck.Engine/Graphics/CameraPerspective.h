#pragma once
#include "Camera.h"

namespace Duck
{
	class CameraPerspective final : public Camera
	{
	public:
		CameraPerspective(const float& fov = 70.f, const float& zNear = .1f, const float& zFar = 100.f);
		virtual void RecalculateProjectionMatrix() override;

	private:
		float _fov;
	};
}