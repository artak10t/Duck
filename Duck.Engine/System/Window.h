#pragma once
#include "../Math/Vector2.h"

namespace Duck::Window
{
	void Init();
	void SwapBuffers();
	void Destroy();
	const bool IsOpen();

	void SetTitle(const char* title);

	void SetFullscreen(bool fullscreen);
	bool GetFullscreen();

	void SetResolution(iVector2 resolution);
	void SetResolution(int width, int height);
	iVector2 GetResolution();

	void SetVSync(bool vsync);
	bool GetVSync();

	float GetAspectRatio();
}