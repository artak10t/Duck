#pragma once

namespace Duck::Window
{
	void Init();
	void SwapBuffers();
	void Destroy();
	const bool IsOpen();

	void Title(const char* title);
	void Fullscreen(bool fullscreen);
	void Resolution(int width, int height);
	const float& AspectRatio();
	void VSync(bool vsync);
}