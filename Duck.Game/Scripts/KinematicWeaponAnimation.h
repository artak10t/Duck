#pragma once
#include <System/Input.h>

class KinematicWeaponAnimation : public Component
{
private:
	Vector2 deltaMouse = { 0, 0 };
	Vector3 finalPosition = { 0, 0, 0 };
	Quaternion finalRotation = { 0, 0, 0, 1 };

	// Bob

	// Recoil
	void recoil(float deltaTime)
	{

	}

	void swayPosition(float deltaTime)
	{
		Vector3 invertLook = Vector3(deltaMouse.x, -deltaMouse.y, 0) * -PositionStep;
		invertLook.x = std::clamp(invertLook.x, -PositionMax, PositionMax);
		invertLook.y = std::clamp(invertLook.y, -PositionMax, PositionMax);
		finalPosition = invertLook;
	}

	void swayRotation(float deltaTime)
	{
		Vector2 look = deltaMouse * RotationStep;
		Quaternion swayRotation = Quaternion::AngleAxis(look.y, { 1, 0, 0 }) * Quaternion::AngleAxis(look.x, { 0, 1, 0 });
		finalRotation = swayRotation;
	}

public:
	// General
	float Smooth = 8;

	// Sway Position
	float PositionStep = 0.005f;
	float PositionMax = 0.075f;

	// Sway Rotation
	float RotationStep = 0.125f;

	void Update(float deltaTime)
	{
		deltaMouse = { 0, 0 };
		if (Input::IsCursorLocked())
			deltaMouse = Input::GetMouseDelta();

		recoil(deltaTime);
		swayPosition(deltaTime);
		swayRotation(deltaTime);

		entity->transform.position = Vector::Lerp(entity->transform.position, finalPosition, deltaTime * Smooth);
		entity->transform.rotation = Quaternion::Slerp(entity->transform.rotation, finalRotation, deltaTime * Smooth);
	}

};