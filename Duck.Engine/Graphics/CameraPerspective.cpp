#include "CameraPerspective.h"
#include "../Math/Trigonometry.h"
#include "../System/Window.h"

namespace Duck
{
	CameraPerspective::CameraPerspective(const float& fov, const float& near, const float& far) : Camera(near, far)
	{
		this->fov = fov;
		RecalculateProjectionMatrix();
	}

	void CameraPerspective::RecalculateProjectionMatrix()
	{
		projection = Matrix::Perspective(Math::ToRadians(fov), Window::GetAspectRatio(), near, far);
	}
}