#include "CameraPerspective.h"
#include "../Math/Trigonometry.h"
#include "../System/Window.h"

namespace Duck
{
	CameraPerspective::CameraPerspective(const float& fov, const float& zNear, const float& zFar) : Camera(zNear, zFar)
	{
		_fov = fov;
		RecalculateProjectionMatrix();
	}

	void CameraPerspective::RecalculateProjectionMatrix()
	{
		_projection = Matrix::Perspective(Math::ToRadians(_fov), Window::AspectRatio(), _near, _far);
	}
}