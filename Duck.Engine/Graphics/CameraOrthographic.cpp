#include "CameraOrthographic.h"
#include "../System/Window.h"

namespace Duck
{
	CameraOrthographic::CameraOrthographic(const float& near, const float& far) : Camera(near, far)
	{
		RecalculateProjectionMatrix();
	}

	void CameraOrthographic::RecalculateProjectionMatrix()
	{
		m_Projection = Matrix::Orthographic(-Window::GetAspectRatio(), Window::GetAspectRatio(), -1.0f, 1.0f, m_Near, m_Far);
	}
}