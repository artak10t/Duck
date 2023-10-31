#pragma once
#include "../Math/Matrix4.h"
#include "../Math/Transform.h"

namespace Duck
{
	class Camera
	{
	public:
		Transform transform;

		static Camera* GetMain();
		static void SetMain(Camera& camera);

		Camera(const float& near = .25f, const float& far = 500.f);
		~Camera();

		const Matrix4& Projection();
		const Matrix4 View();
		virtual void RecalculateProjectionMatrix() = 0;

	private:
		static Camera* mainCamera;

	protected:
		float near = .25f, far = 500.f;
		Matrix4 projection = Matrix4(1);
		Matrix4 m_View = Matrix4(1);
	};
}