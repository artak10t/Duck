#include "Camera.h"
#include <glfw/glfw3.h>

namespace Duck
{
	Camera* Camera::mainCamera = nullptr;

	Camera* Camera::GetMain()
	{
		return mainCamera;
	}

	void Camera::SetMain(Camera& camera)
	{
		camera.RecalculateProjectionMatrix();
		mainCamera = &camera;
	}

	Camera::Camera(const float& near, const float& far)
	{
		if (!Camera::mainCamera)
			Camera::mainCamera = this;

		this->near = near;
		this->far = far;
	}

	Camera::~Camera()
	{
		if (Camera::mainCamera && Camera::mainCamera == this)
			Camera::mainCamera = nullptr;
	}

	const Matrix4& Camera::Projection()
	{
		return projection;
	}

	const Matrix4 Camera::View()
	{
		return Matrix::Inverse(transform.LocalToWorld());
	}
}