#pragma once

namespace FlyCamera
{
	bool wireframe = false;
	bool fullscreen = false;
	float speed = 1;
	float mouseSensitivity = 0.15f;

	void Update(float deltaTime)
	{
		if (Input::IsKeyPressed(Input::W))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Forward() * deltaTime * speed;
		else if (Input::IsKeyPressed(Input::S))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Forward() * deltaTime * speed;
		if (Input::IsKeyPressed(Input::D))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Right() * deltaTime * speed;
		else if (Input::IsKeyPressed(Input::A))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Right() * deltaTime * speed;
		if (Input::IsKeyPressed(Input::E))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Up() * deltaTime * speed;
		else if (Input::IsKeyPressed(Input::Q))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Up() * deltaTime * speed;

		speed = std::clamp(speed + Input::GetMouseScroll().y, 1.f, 1000.f);

		if (Input::IsKeyDown(Input::Tab))
		{
			fullscreen = !fullscreen;
			Input::SetCursorLock(fullscreen);
		}

		if (Input::IsKeyDown(Input::V))
		{
			wireframe = !wireframe;

			if (wireframe)
				Renderer::SetView(Renderer::View::Wireframe);
			else
				Renderer::SetView(Renderer::View::Shaded);
		}

		if (fullscreen)
		{
			Vector2 delta = Input::GetMouseDelta() * mouseSensitivity;
			Quaternion rotation = Camera::GetMain()->transform.rotation;
			Quaternion horiz = Quaternion::AngleAxis(delta.x, { 0, 1, 0 });
			Quaternion vert = Quaternion::AngleAxis(delta.y, { 1, 0, 0 });
			Camera::GetMain()->transform.rotation = horiz * rotation * vert;
		}
	}
}