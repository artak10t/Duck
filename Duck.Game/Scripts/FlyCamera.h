#pragma once

namespace FlyCamera
{
	bool wireframe = false;
	bool fullscreen = false;
	float speed = 1;
	float mouseSensitivity = 0.15f;

	void Update(float deltaTime)
	{
		if (Input::KeyPress(Input::W))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Forward() * deltaTime * speed;
		else if (Input::KeyPress(Input::S))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Forward() * deltaTime * speed;
		if (Input::KeyPress(Input::D))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Right() * deltaTime * speed;
		else if (Input::KeyPress(Input::A))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Right() * deltaTime * speed;
		if (Input::KeyPress(Input::E))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Up() * deltaTime * speed;
		else if (Input::KeyPress(Input::Q))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Up() * deltaTime * speed;

		speed = std::clamp(speed + Input::MouseScrollDelta().y, 1.f, 1000.f);

		if (Input::KeyDown(Input::MouseRight))
		{
			fullscreen = !fullscreen;
			Input::LockCursor(fullscreen);
		}

		if (Input::KeyDown(Input::V))
		{
			wireframe = !wireframe;

			if (wireframe)
				Renderer::ShadingMode(Renderer::PolygonMode::Wireframe);
			else
				Renderer::ShadingMode(Renderer::PolygonMode::Shaded);
		}

		if (fullscreen)
		{
			Vector2 delta = Input::MouseDelta() * mouseSensitivity;
			Quaternion rotation = Camera::GetMain()->transform.rotation;
			Quaternion horiz = Quaternion::AngleAxis(delta.x, { 0, 1, 0 });
			Quaternion vert = Quaternion::AngleAxis(delta.y, { 1, 0, 0 });
			Camera::GetMain()->transform.rotation = horiz * rotation * vert;
		}
	}
}