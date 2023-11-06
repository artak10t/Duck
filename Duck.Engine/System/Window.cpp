#include "Window.h"
#include "../pch.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../Renderer/Renderer.h"
#include "../Renderer/Camera.h"

#define OPENGL_MAJOR 4
#define OPENGL_MINOR 3

#define DEFAULT_TITLE "App"
#define DEFAULT_VSYNC true
#define DEFAULT_FULLSCREEN false
#define DEFAULT_MAXIMIZED false
#define DEFAULT_RESOLUTION_WIDTH 800
#define DEFAULT_RESOLUTION_HEIGHT 600

namespace Duck::Window
{
	// OpenGL
	static GLFWwindow* glfw_window = nullptr;
	static GLFWmonitor* glfw_monitor = nullptr;
	static const GLFWvidmode* glfw_vidmode = nullptr;

	// Window
	static bool vsync = DEFAULT_VSYNC;
	static bool fullscreen = DEFAULT_FULLSCREEN;
	static iVector2 lastResolution = { 0, 0 };
	static iVector2 lastSize = { 0, 0 };
	static iVector2 lastPosition = { 0, 0 };
	static float aspect = 1.6f;

	static void UpdateCamera(int width, int height)
	{
		if (Camera::GetMain())
			Camera::GetMain()->RecalculateProjectionMatrix();
	}

	static void OnFramebufferSize(GLFWwindow* window, int width, int height)
	{
		if (!width || !height)
			return;

		aspect = static_cast<float>(width) / height;
		UpdateCamera(width, height);
		glViewport(0, 0, width, height);
	}

	void Init()
	{
		// Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfw_monitor = glfwGetPrimaryMonitor();
		glfw_vidmode = glfwGetVideoMode(glfw_monitor);

		glfwWindowHint(GLFW_MAXIMIZED, DEFAULT_MAXIMIZED);

		// Create Window
		if (DEFAULT_MAXIMIZED)
		{
			glfw_window = glfwCreateWindow(glfw_vidmode->width, glfw_vidmode->height, DEFAULT_TITLE, NULL, NULL);
			lastResolution.x = glfw_vidmode->width;
			lastResolution.y = glfw_vidmode->height;
			aspect = static_cast<float>(glfw_vidmode->width) / glfw_vidmode->height;
		}
		else
		{
			glfw_window = glfwCreateWindow(DEFAULT_RESOLUTION_WIDTH, DEFAULT_RESOLUTION_HEIGHT, DEFAULT_TITLE, NULL, NULL);
			lastResolution.x = DEFAULT_RESOLUTION_WIDTH;
			lastResolution.y = DEFAULT_RESOLUTION_HEIGHT;
			aspect = static_cast<float>(DEFAULT_RESOLUTION_WIDTH) / DEFAULT_RESOLUTION_HEIGHT;
		}

		assert(glfw_window != nullptr);

		// Set Context
		glfwMakeContextCurrent(glfw_window);
		glfwSetFramebufferSizeCallback(glfw_window, OnFramebufferSize);

		// Initialize Renderer
		Renderer::Init();

		glViewport(0, 0, lastResolution.x, lastResolution.y);
		UpdateCamera(lastResolution.x, lastResolution.y);

		glfwSwapInterval(DEFAULT_VSYNC);
		SetFullscreen(DEFAULT_FULLSCREEN);
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(glfw_window);
	}

	void Destroy()
	{
		glfwDestroyWindow(glfw_window);
		glfwTerminate();
	}

	const bool IsOpen()
	{
		return !glfwWindowShouldClose(glfw_window);
	}

	void SetTitle(const char* title)
	{
		glfwSetWindowTitle(glfw_window, title);
	}

	void SetFullscreen(bool state)
	{
		fullscreen = state;

		if (fullscreen)
		{
			glfwGetWindowPos(glfw_window, &lastPosition.x, &lastPosition.y);
			glfwGetWindowSize(glfw_window, &lastSize.x, &lastSize.y);
			glfwSetWindowMonitor(glfw_window, glfw_monitor, 0, 0, lastResolution.x, lastResolution.y, glfw_vidmode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(glfw_window, NULL, lastPosition.x, lastPosition.y, lastSize.x, lastSize.y, 0);
		}

		SetVSync(vsync);
	}

	bool GetFullscreen()
	{
		return fullscreen;
	}

	void SetResolution(iVector2 resolution)
	{
		glfwRestoreWindow(glfw_window);
		glfwSetWindowSize(glfw_window, resolution.x, resolution.y);
		lastResolution.x = resolution.x;
		lastResolution.y = resolution.y;
		lastSize.x = resolution.x;
		lastSize.y = resolution.y;
	}

	void SetResolution(int width, int height)
	{
		SetResolution({ width, height });
	}

	iVector2 GetResolution()
	{
		return lastResolution;
	}

	void SetVSync(bool state)
	{
		vsync = state;

		glfwSwapInterval(vsync);
	}

	bool GetVSync()
	{
		return vsync;
	}

	float GetAspectRatio()
	{
		return aspect;
	}
}