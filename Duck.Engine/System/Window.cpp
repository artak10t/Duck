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
	// OpenGL
	static GLFWwindow* m_Window = nullptr;
	static GLFWmonitor* m_Monitor = nullptr;
	static const GLFWvidmode* m_Vidmode = nullptr;

	// Window
	static bool m_Vsync = DEFAULT_VSYNC;
	static int m_LastResolutionWidth = 0, m_LastResolutionHeight = 0;
	static int m_LastWidth = 0, m_LastHeight = 0;
	static int m_LastPosX = 0, m_LastPosY = 0;
	static float m_Aspect = 1.6f;

	static void UpdateCamera(int width, int height)
	{
		if (Camera::GetMain())
			Camera::GetMain()->RecalculateProjectionMatrix();
	}

	static void OnFramebufferSize(GLFWwindow* window, int width, int height)
	{
		if (!width || !height)
			return;

		m_Aspect = static_cast<float>(width) / height;
		UpdateCamera(width, height);
		glViewport(0, 0, width, height);
	}

	void Init()
	{
		// Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Monitor = glfwGetPrimaryMonitor();
		m_Vidmode = glfwGetVideoMode(m_Monitor);

		glfwWindowHint(GLFW_MAXIMIZED, DEFAULT_MAXIMIZED);

		// Create Window
		if (DEFAULT_MAXIMIZED)
		{
			m_Window = glfwCreateWindow(m_Vidmode->width, m_Vidmode->height, DEFAULT_TITLE, NULL, NULL);
			m_LastResolutionWidth = m_Vidmode->width;
			m_LastResolutionHeight = m_Vidmode->height;
			m_Aspect = static_cast<float>(m_Vidmode->width) / m_Vidmode->height;
		}
		else
		{
			m_Window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_TITLE, NULL, NULL);
			m_LastResolutionWidth = DEFAULT_WIDTH;
			m_LastResolutionHeight = DEFAULT_HEIGHT;
			m_Aspect = static_cast<float>(DEFAULT_WIDTH) / DEFAULT_HEIGHT;
		}

		assert(m_Window != nullptr);

		// Set Context
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, OnFramebufferSize);

		// Initialize Renderer
		Renderer::Init();

		glViewport(0, 0, m_LastResolutionWidth, m_LastResolutionHeight);
		UpdateCamera(m_LastResolutionWidth, m_LastResolutionHeight);

		glfwSwapInterval(DEFAULT_VSYNC);
		SetFullscreen(DEFAULT_FULLSCREEN);
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	const bool IsOpen()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void SetTitle(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
	}

	void SetFullscreen(bool fullscreen)
	{
		if (fullscreen)
		{
			glfwGetWindowPos(m_Window, &m_LastPosX, &m_LastPosY);
			glfwGetWindowSize(m_Window, &m_LastWidth, &m_LastHeight);
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, m_LastResolutionWidth, m_LastResolutionHeight, m_Vidmode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(m_Window, NULL, m_LastPosX, m_LastPosY, m_LastWidth, m_LastHeight, 0);
		}

		SetVSync(m_Vsync);
	}

	void SetResolution(int width, int height)
	{
		glfwRestoreWindow(m_Window);
		glfwSetWindowSize(m_Window, width, height);
		m_LastResolutionWidth = width;
		m_LastResolutionHeight = height;
		m_LastWidth = width;
		m_LastHeight = height;
	}

	const float& GetAspectRatio()
	{
		return m_Aspect;
	}

	void SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		m_Vsync = vsync;
	}
}