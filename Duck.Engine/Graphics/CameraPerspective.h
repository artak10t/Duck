#pragma once
#include "Camera.h"

namespace Duck
{
	class CameraPerspective final : public Camera
	{
	public:
		CameraPerspective(const float& fov = 70.f, const float& near = .1f, const float& far = 500.f);
		virtual void RecalculateProjectionMatrix() override;

	private:
		float m_Fov;
	};
}