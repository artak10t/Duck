#pragma once
#include <System/Input.h>
#include <Graphics/Camera.h>
#include <Graphics/Renderer.h>

using namespace Duck;

namespace FlyCamera
{
	bool m_Wireframe = false;
	bool m_Fullscreen = false;
	float m_Speed = 1;
	float m_MouseSensitivity = 0.15f;

	void Update(float deltaTime)
	{
		if (Input::IsKeyPressed(Input::W))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Forward() * deltaTime * m_Speed;
		else if (Input::IsKeyPressed(Input::S))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Forward() * deltaTime * m_Speed;
		if (Input::IsKeyPressed(Input::D))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Right() * deltaTime * m_Speed;
		else if (Input::IsKeyPressed(Input::A))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Right() * deltaTime * m_Speed;
		if (Input::IsKeyPressed(Input::E))
			Camera::GetMain()->transform.position += Camera::GetMain()->transform.Up() * deltaTime * m_Speed;
		else if (Input::IsKeyPressed(Input::Q))
			Camera::GetMain()->transform.position -= Camera::GetMain()->transform.Up() * deltaTime * m_Speed;

		m_Speed = std::clamp(m_Speed + Input::GetMouseScroll().y, 1.f, 1000.f);

		if (Input::IsKeyDown(Input::Tab))
		{
			m_Fullscreen = !m_Fullscreen;
			Input::SetCursorLock(m_Fullscreen);
		}

		if (Input::IsKeyDown(Input::V))
		{
			m_Wireframe = !m_Wireframe;

			if (m_Wireframe)
				Renderer::SetView(Renderer::View::Wireframe);
			else
				Renderer::SetView(Renderer::View::Shaded);
		}

		if (m_Fullscreen)
		{
			Vector2 delta = Input::GetMouseDelta() * m_MouseSensitivity;
			Quaternion rotation = Camera::GetMain()->transform.rotation;
			Quaternion horiz = Quaternion::AngleAxis(delta.x, { 0, 1, 0 });
			Quaternion vert = Quaternion::AngleAxis(delta.y, { 1, 0, 0 });
			Camera::GetMain()->transform.rotation = horiz * rotation * vert;
		}
	}
}