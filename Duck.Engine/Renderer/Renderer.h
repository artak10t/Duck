#pragma once
#include "Camera.h"
#include "Light.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "../Math/Vector4.h"

namespace Duck
{
	class Renderer
	{
	public:
		enum class View
		{
			Shaded,
			Wireframe
		};

		// Light
		static Light AmbientLight;
		static LightDirectional DirectionalLight;
		friend struct LightPoint;
		friend struct LightSpot;

		// Ambient
		static Vector4 BackgroundColor;

		static void Init();
		static void ClearBuffer();
		static void UpdateCameraUBO();
		static void UpdateLightUBO();
		static void SetView(View mode);
		static View GetView();

	private:
		static View viewMode;
		static std::vector<LightPoint*> pointLights;
		static std::vector<LightSpot*> spotLights;

		static unsigned int cameraUBO;
		static unsigned int lightUBO;
	};
}