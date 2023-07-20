#include "CameraPerspective.h"
#include "../Math/Trigonometry.h"
#include "../System/Window.h"

namespace Duck
{
	CameraPerspective::CameraPerspective(const float& fov, const float& near, const float& far) : Camera(near, far)
	{
		m_Fov = fov;
		RecalculateProjectionMatrix();
	}

	void CameraPerspective::RecalculateProjectionMatrix()
	{
		m_Projection = Matrix::Perspective(Math::ToRadians(m_Fov), Window::GetAspectRatio(), m_Near, m_Far);
	}
}