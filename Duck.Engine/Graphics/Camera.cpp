#include "Camera.h"
#include <glfw/glfw3.h>

namespace Duck
{
	Camera* Camera::_main = nullptr;

	Camera* Camera::GetMain()
	{
		return _main;
	}

	void Camera::SetMain(Camera& camera)
	{
		camera.RecalculateProjectionMatrix();
		_main = &camera;
	}

	Camera::Camera(const float& zNear, const float& zFar)
	{
		if (!Camera::_main)
			Camera::_main = this;

		_near = zNear;
		_far = zFar;
	}

	Camera::~Camera()
	{
		if (Camera::_main && Camera::_main == this)
			Camera::_main = nullptr;
	}

	const Matrix4& Camera::Projection()
	{
		return _projection;
	}

	const Matrix4 Camera::View()
	{
		return Matrix::Inverse(transform.LocalToWorld());
	}
}