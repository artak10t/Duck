#pragma once
#include <System/Input.h>
#include <Graphics/Camera.h>
#include <Graphics/Renderer.h>
#include <System/Window.h>

using namespace Duck;

namespace FlyCamera
{
	float speed = 1;
	float mouseSensitivity = 0.15f;

	void Update(float deltaTime)
	{
		if (Input::GetKey(Input::W))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Forward() * deltaTime * speed;
		else if (Input::GetKey(Input::S))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Forward() * deltaTime * speed;
		if (Input::GetKey(Input::D))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Right() * deltaTime * speed;
		else if (Input::GetKey(Input::A))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Right() * deltaTime * speed;
		if (Input::GetKey(Input::E))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Up() * deltaTime * speed;
		else if (Input::GetKey(Input::Q))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Up() * deltaTime * speed;

		speed = std::clamp(speed + Input::GetMouseScroll().y, 1.f, 1000.f);

		if (Input::GetKeyDown(Input::Tab))
			Input::SetCursorLock(!Input::GetCursorLocked());

		if (Input::GetKeyDown(Input::V))
		{
			if (Renderer::GetView() != Renderer::View::Wireframe)
				Renderer::SetView(Renderer::View::Wireframe);
			else
				Renderer::SetView(Renderer::View::Shaded);
		}

		if (Input::GetCursorLocked())
		{
			Vector2 delta = Input::GetMouseDelta() * mouseSensitivity;
			Quaternion rotation = Camera::GetMain()->transform.rotation;
			Quaternion horiz = Quaternion::AngleAxis(delta.x, { 0, 1, 0 });
			Quaternion vert = Quaternion::AngleAxis(delta.y, { 1, 0, 0 });
			Camera::GetMain()->transform.rotation = horiz * rotation * vert;
		}
	}
}