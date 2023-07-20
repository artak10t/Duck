#include "Camera.h"
#include <glfw/glfw3.h>

namespace Duck
{
	Camera* Camera::m_MainCamera = nullptr;

	Camera* Camera::GetMain()
	{
		return m_MainCamera;
	}

	void Camera::SetMain(Camera& camera)
	{
		camera.RecalculateProjectionMatrix();
		m_MainCamera = &camera;
	}

	Camera::Camera(const float& near, const float& far)
	{
		if (!Camera::m_MainCamera)
			Camera::m_MainCamera = this;

		m_Near = near;
		m_Far = far;
	}

	Camera::~Camera()
	{
		if (Camera::m_MainCamera && Camera::m_MainCamera == this)
			Camera::m_MainCamera = nullptr;
	}

	const Matrix4& Camera::Projection()
	{
		return m_Projection;
	}

	const Matrix4 Camera::View()
	{
		return Matrix::Inverse(transform.LocalToWorld());
	}
}