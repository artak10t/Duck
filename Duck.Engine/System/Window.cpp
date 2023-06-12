#include "Window.h"
#include "../pch.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../Graphics/Renderer.h"
#include "../Graphics/Camera.h"

#define DEFAULT_TITLE "App"
#define DEFAULT_VSYNC true
#define DEFAULT_FULLSCREEN false
#define DEFAULT_MAXIMIZED false
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

namespace Duck::Window
{
	//Remove dependency from OpenGL
	//REFACTOR ALL CODE, Clearer code for _lastPosition, _lastWidth, _lastResoultion

	// OpenGL
	static GLFWwindow* window = nullptr;
	static GLFWmonitor* monitor = nullptr;
	static const GLFWvidmode* vidmode = nullptr;

	// Window
	static bool vsync = DEFAULT_VSYNC;
	static int lastResolutionWidth = 0, lastResolutionHeight = 0;
	static int lastWidth = 0, lastHeight = 0;
	static int lastPosX = 0, lastPosY = 0;
	static float aspect = 1.6f;

	static void cameraUpdate(int width, int height)
	{
		if (Camera::GetMain())
			Camera::GetMain()->RecalculateProjectionMatrix();
	}

	static void onFramebufferSize(GLFWwindow* window, int width, int height)
	{
		if (!width || !height)
			return;

		aspect = static_cast<float>(width) / height;
		cameraUpdate(width, height);
		glViewport(0, 0, width, height);
	}

	void Init()
	{
		// Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		monitor = glfwGetPrimaryMonitor();
		vidmode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_MAXIMIZED, DEFAULT_MAXIMIZED);

		// Create Window
		if (DEFAULT_MAXIMIZED)
		{
			window = glfwCreateWindow(vidmode->width, vidmode->height, DEFAULT_TITLE, NULL, NULL);
			lastResolutionWidth = vidmode->width;
			lastResolutionHeight = vidmode->height;
			aspect = static_cast<float>(vidmode->width) / vidmode->height;
		}
		else
		{
			window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE, NULL, NULL);
			lastResolutionWidth = DEFAULT_WIDTH;
			lastResolutionHeight = DEFAULT_HEIGHT;
			aspect = static_cast<float>(DEFAULT_WIDTH) / DEFAULT_HEIGHT;
		}

		assert(window != nullptr);

		// Set Context
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, onFramebufferSize);

		// Initialize Renderer
		Renderer::Init();

		glViewport(0, 0, lastResolutionWidth, lastResolutionHeight);
		cameraUpdate(lastResolutionWidth, lastResolutionHeight);

		glfwSwapInterval(DEFAULT_VSYNC);
		SetFullscreen(DEFAULT_FULLSCREEN);
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Destroy()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	const bool IsOpen()
	{
		return !glfwWindowShouldClose(window);
	}

	void SetTitle(const char* title)
	{
		glfwSetWindowTitle(window, title);
	}

	void SetFullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			glfwGetWindowPos(window, &lastPosX, &lastPosY);
			glfwGetWindowSize(window, &lastWidth, &lastHeight);
			glfwSetWindowMonitor(window, monitor, 0, 0, lastResolutionWidth, lastResolutionHeight, vidmode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(window, NULL, lastPosX, lastPosY, lastWidth, lastHeight, 0);
		}

		SetVSync(vsync);
	}

	void SetResolution(int width, int height)
	{
		glfwRestoreWindow(window);
		glfwSetWindowSize(window, width, height);
		lastResolutionWidth = width;
		lastResolutionHeight = height;
		lastWidth = width;
		lastHeight = height;
	}

	const float& GetAspectRatio()
	{
		return aspect;
	}

	void SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		vsync = vsync;
	}
}