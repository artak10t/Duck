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
		Camera(const float& zNear = .1f, const float& zFar = 100.f);
		~Camera();

		const Matrix4& Projection();
		const Matrix4 View();
		virtual void RecalculateProjectionMatrix() = 0;

	protected:
		float _near = .1f, _far = 100.f;
		Matrix4 _projection = Matrix4(1);
		Matrix4 _view = Matrix4(1);

	private:
		static Camera* _main;
	};
}