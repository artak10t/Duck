#pragma once

namespace Duck::Window
{
	void Init();
	void SwapBuffers();
	void Destroy();
	const bool IsOpen();

	void SetTitle(const char* title);
	void SetFullscreen(bool fullscreen);
	void SetResolution(int width, int height);
	void SetVSync(bool vsync);

	const float& GetAspectRatio();
}