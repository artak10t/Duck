#pragma once
#include "Camera.h"
#include "Light.h"
#include "LightDirectional.h"
#include "../Math/Vector4.h"

namespace Duck::Renderer
{
	inline Light AmbientLight;
	inline LightDirectional DirectionalLight;

	enum class View
	{
		Shaded,
		Wireframe
	};

	// Default buffer color after clear.
	inline Vector4 BackgroundColor = { 0.6f, 0.7f, 0.9f, 1 };

	// Initialization of renderer. Should be done after window creation.
	void Init();

	// Clear current window's buffer.
	void ClearBuffer();

	// Updates global uniform data for all shader programs.
	void UpdateGlobalUBO();

	// Renderer shading mode.
	void SetView(View mode);
	View GetView();
}