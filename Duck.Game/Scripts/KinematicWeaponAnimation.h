#pragma once
#include <System/Input.h>

class KinematicWeaponAnimation : public Component
{
private:
	Vector2 _deltaMouse = { 0, 0 };

	//Bob Animation

	//Recoil Animation

	void SwayPosition(float deltaTime)
	{
		Vector3 invertLook = Vector3(_deltaMouse.x, -_deltaMouse.y, 0) * -PositionStep;
		invertLook.x = std::clamp(invertLook.x, -PositionMax, PositionMax);
		invertLook.y = std::clamp(invertLook.y, -PositionMax, PositionMax);
		entity->transform.position = Vector::Lerp(entity->transform.position, invertLook, deltaTime * Smooth);
	}

	void SwayRotation(float deltaTime)
	{
		Vector2 look = _deltaMouse * RotationStep;
		Quaternion targetRotation = Quaternion::AngleAxis(look.y, { 1, 0, 0 }) * Quaternion::AngleAxis(look.x, { 0, 1, 0 });
		entity->transform.rotation = Quaternion::Slerp(entity->transform.rotation, targetRotation, deltaTime * Smooth);
	}

public:
	//General
	float Smooth = 8;

	//Sway Position
	float PositionStep = 0.025f;
	float PositionMax = 0.125f;

	//Sway Rotation
	float RotationStep = 0.125f;

	void Update(float deltaTime)
	{
		_deltaMouse = { 0, 0 };
		if (Input::IsCursorLocked())
			_deltaMouse = Input::MouseDelta();

		SwayPosition(deltaTime);
		SwayRotation(deltaTime);
	}

};