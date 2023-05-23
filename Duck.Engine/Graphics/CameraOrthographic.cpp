#include "CameraOrthographic.h"
#include "../System/Window.h"

namespace Duck
{
	CameraOrthographic::CameraOrthographic(const float& zNear, const float& zFar) : Camera(zNear, zFar)
	{
		RecalculateProjectionMatrix();
	}

	void CameraOrthographic::RecalculateProjectionMatrix()
	{
		_projection = Matrix::Orthographic(-Window::AspectRatio(), Window::AspectRatio(), -1.0f, 1.0f, _near, _far);
	}
}