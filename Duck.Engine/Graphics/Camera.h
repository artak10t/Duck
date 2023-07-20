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

		Camera(const float& near = .1f, const float& far = 100.f);
		~Camera();

		const Matrix4& Projection();
		const Matrix4 View();
		virtual void RecalculateProjectionMatrix() = 0;

	private:
		static Camera* m_MainCamera;

	protected:
		float m_Near = .1f, m_Far = 100.f;
		Matrix4 m_Projection = Matrix4(1);
		Matrix4 m_View = Matrix4(1);
	};
}