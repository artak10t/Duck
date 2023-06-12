#pragma once
#include "../Math/Matrix4.h"
#include "../Math/Transform.h"

//Needs refactoring
namespace Duck
{
	class Camera
	{
	public:
		static Camera* GetMain();
		static void SetMain(Camera& camera);

		Transform transform;
		Camera(const float& near = .1f, const float& far = 100.f);
		~Camera();

		const Matrix4& Projection();
		const Matrix4 View();
		virtual void RecalculateProjectionMatrix() = 0;

	private:
		static Camera* main;

	protected:
		float near = .1f, far = 100.f;
		Matrix4 projection = Matrix4(1);
		Matrix4 view = Matrix4(1);
	};
}