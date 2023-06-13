#pragma once

class KinematicWeaponAnimation : public Component
{
private:
	Vector2 deltaMouse = { 0, 0 };
	Vector3 targetPosition = { 0, 0, 0 };
	Quaternion targetRotation = { 0, 0, 0, 1 };

	// Bob

	// Recoil

	void swayPosition(float deltaTime)
	{
		Vector3 invertLook = Vector3(deltaMouse.x, -deltaMouse.y, 0) * -SwayPositionStep;
		invertLook.x = std::clamp(invertLook.x, -SwayPositionMax, SwayPositionMax);
		invertLook.y = std::clamp(invertLook.y, -SwayPositionMax, SwayPositionMax);
		targetPosition = invertLook;
	}

	void swayRotation(float deltaTime)
	{
		Vector2 look = deltaMouse * SwayRotationStep;
		Quaternion swayRotation = Quaternion::AngleAxis(look.y, { 1, 0, 0 }) * Quaternion::AngleAxis(look.x, { 0, 1, 0 });
		targetRotation = swayRotation;
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
		// custom smooth for kickback recoil
		// custom recoil smoothness, custom recoil initial going back animation
		targetPosition.z -= RecoilKickback;
		targetRotation += Quaternion({ RecoilOffset.x, Random::Range(-RecoilOffset.y, RecoilOffset.y), Random::Range(-RecoilOffset.z, RecoilOffset.z) });
	}

	void Update(float deltaTime)
	{
 		deltaMouse = { 0, 0 };
		if (Input::IsCursorLocked())
			deltaMouse = Input::GetMouseDelta();

		swayPosition(deltaTime);
		swayRotation(deltaTime);

		if (Input::IsKeyDown(Input::MouseLeft) && Input::IsCursorLocked())
			CallRecoil();

		entity->transform.position = Vector::Lerp(entity->transform.position, targetPosition, deltaTime * Smooth);
		entity->transform.rotation = Quaternion::Slerp(entity->transform.rotation, targetRotation, deltaTime * Smooth);
	}
};