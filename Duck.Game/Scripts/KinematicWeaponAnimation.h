#pragma once
#include <Scene/Component.h>
#include <Scene/Entity.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <Math/Random.h>
#include <System/Input.h>

using namespace Duck;

class KinematicWeaponAnimation : public Component
{
private:
	Vector2 m_DeltaMouse = { 0, 0 };
	Vector3 m_TargetPosition = { 0, 0, 0 };
	Quaternion m_TargetRotation = { 0, 0, 0, 1 };

	// Bob

	void SwayPosition(float deltaTime)
	{
		Vector3 invertLook = Vector3(m_DeltaMouse.x, -m_DeltaMouse.y, 0) * -SwayPositionStep;
		invertLook.x = std::clamp(invertLook.x, -SwayPositionMax, SwayPositionMax);
		invertLook.y = std::clamp(invertLook.y, -SwayPositionMax, SwayPositionMax);
		m_TargetPosition = invertLook;
	}

	void SwayRotation(float deltaTime)
	{
		Vector2 look = m_DeltaMouse * SwayRotationStep;
		Quaternion swayRotation = Quaternion::AngleAxis(look.y, { 1, 0, 0 }) * Quaternion::AngleAxis(look.x, { 0, 1, 0 });
		m_TargetRotation = swayRotation;
	}

public:
	// General
	float Smooth = 8;

	// Recoil
	Vector3 RecoilOffset = { -20.f, 20.f, 30.f };
	float RecoilKickback = 1.f;

	// Sway Position
	float SwayPositionStep = .005f;
	float SwayPositionMax = .075f;

	// Sway Rotation
	float SwayRotationStep = .125f;

	void CallRecoil()
	{
		m_TargetPosition.z -= RecoilKickback;
		m_TargetRotation += Quaternion({ RecoilOffset.x, Random::Range(-RecoilOffset.y, RecoilOffset.y), Random::Range(-RecoilOffset.z, RecoilOffset.z) });
	}

	void Update(float deltaTime)
	{
 		m_DeltaMouse = { 0, 0 };
		if (Input::IsCursorLocked())
			m_DeltaMouse = Input::GetMouseDelta();

		SwayPosition(deltaTime);
		SwayRotation(deltaTime);

		if (Input::IsKeyDown(Input::MouseLeft) && Input::IsCursorLocked())
			CallRecoil();

		entity->transform.position = Vector::Lerp(entity->transform.position, m_TargetPosition, deltaTime * Smooth);
		entity->transform.rotation = Quaternion::Slerp(entity->transform.rotation, m_TargetRotation, deltaTime * Smooth);
	}
};