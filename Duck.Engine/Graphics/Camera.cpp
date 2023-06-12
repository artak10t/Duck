#include "Camera.h"
#include <glfw/glfw3.h>

namespace Duck
{
	Camera* Camera::main = nullptr;

	Camera* Camera::GetMain()
	{
		return main;
	}

	void Camera::SetMain(Camera& camera)
	{
		camera.RecalculateProjectionMatrix();
		main = &camera;
	}

	Camera::Camera(const float& near, const float& far)
	{
		if (!Camera::main)
			Camera::main = this;

		this->near = near;
		this->far = far;
	}

	Camera::~Camera()
	{
		if (Camera::main && Camera::main == this)
			Camera::main = nullptr;
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