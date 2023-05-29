#include "Window.h"
#include "../pch.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../Graphics/Renderer.h"
#include "../Graphics/Camera.h"

#define DEFAULT_TITLE "App"
#define DEFAULT_VSYNC true
#define DEFAULT_FULLSCREEN false
#define DEFAULT_MAXIMIZED true

namespace Duck::Window
{
	//Remove dependency from OpenGL
	//Clearer code for _lastPosition, _lastWidth, _lastResoultion
	//Make things above more logical and clean
	static GLFWwindow* _window = nullptr;
	static GLFWmonitor* _monitor = nullptr;
	static const GLFWvidmode* _video = nullptr;
	static bool _vsync = DEFAULT_VSYNC;
	static int _lastResolutionWidth = 0, _lastResolutionHeight = 0;
	static int _lastWidth = 0, _lastHeight = 0;
	static int _lastPosX = 0, _lastPosY = 0;
	static float _aspect = 1.6f;

	static void _cameraUpdate(int width, int height)
	{
		if (Camera::GetMain())
			Camera::GetMain()->RecalculateProjectionMatrix();
	}

	static void _reizeCallback(GLFWwindow* window, int width, int height)
	{
		if (!width || !height)
			return;

		_aspect = static_cast<float>(width) / height;
		_cameraUpdate(width, height);
		glViewport(0, 0, width, height);
	}

	void Init()
	{
		// Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_monitor = glfwGetPrimaryMonitor();
		_video = glfwGetVideoMode(_monitor);

		glfwWindowHint(GLFW_MAXIMIZED, DEFAULT_MAXIMIZED);

		// Create Window
		_window = glfwCreateWindow(_video->width, _video->height, DEFAULT_TITLE, NULL, NULL);
		_lastResolutionWidth = _video->width;
		_lastResolutionHeight = _video->height;
		_aspect = static_cast<float>(_video->width) / _video->height;

		assert(_window != nullptr);

		// Set Context
		glfwMakeContextCurrent(_window);
		glfwSetFramebufferSizeCallback(_window, _reizeCallback);

		// Initialize Renderer
		Renderer::Init();

		glViewport(0, 0, _lastResolutionWidth, _lastResolutionHeight);
		_cameraUpdate(_lastResolutionWidth, _lastResolutionHeight);

		glfwSwapInterval(DEFAULT_VSYNC);
		Fullscreen(DEFAULT_FULLSCREEN);
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	void Destroy()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	const bool IsOpen()
	{
		return !glfwWindowShouldClose(_window);
	}

	void Title(const char* title)
	{
		glfwSetWindowTitle(_window, title);
	}

	void Fullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			glfwGetWindowPos(_window, &_lastPosX, &_lastPosY);
			glfwGetWindowSize(_window, &_lastWidth, &_lastHeight);
			glfwSetWindowMonitor(_window, _monitor, 0, 0, _lastResolutionWidth, _lastResolutionHeight, _video->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(_window, NULL, _lastPosX, _lastPosY, _lastWidth, _lastHeight, 0);
		}

		VSync(_vsync);
	}

	void Resolution(int width, int height)
	{
		glfwRestoreWindow(_window);
		glfwSetWindowSize(_window, width, height);
		_lastResolutionWidth = width;
		_lastResolutionHeight = height;
		_lastWidth = width;
		_lastHeight = height;
	}

	const float& AspectRatio()
	{
		return _aspect;
	}

	void VSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		_vsync = vsync;
	}
}