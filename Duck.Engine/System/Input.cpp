#include "input.h"
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Duck::Input
{
	static GLFWwindow* m_Window = nullptr;

	// Keyboard
	struct KeyState
	{
		bool down = false;
		bool pressed = false;
		bool up = false;
	};
	static std::unordered_map<int, KeyState> m_KeyMap = {};


	//Mouse
	static bool m_IsCursorLocked = false;
	static Vector2 m_MouseLastPosition = { 0, 0 };
	static Vector2 m_MouseDelta = { 0, 0 };
	static Vector2 m_MousePosition = { 0, 0 };
	static Vector2 m_MouseScroll = { 0, 0 };

	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			m_KeyMap[key].down = true;
			m_KeyMap[key].pressed = true;
			m_KeyMap[key].up = false;
			break;
		case GLFW_RELEASE:
			m_KeyMap[key].down = false;
			m_KeyMap[key].pressed = false;
			m_KeyMap[key].up = true;
			break;
		}
	}

	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		OnKey(window, button, -1, action, mods);
	}

	static void OnMousePosition(GLFWwindow* window, double x, double y)
	{
		m_MousePosition.x = static_cast<float>(x);
		m_MousePosition.y = static_cast<float>(y);
	}

	static void OnMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
	{
		m_MouseScroll.x = static_cast<float>(deltaX);
		m_MouseScroll.y = static_cast<float>(deltaY);
	}


	void Init()
	{
		m_Window = glfwGetCurrentContext();

		assert(m_Window != NULL);

		glfwSetKeyCallback(m_Window, OnKey);
		glfwSetMouseButtonCallback(m_Window, OnMouseButton);
		glfwSetCursorPosCallback(m_Window, OnMousePosition);
		glfwSetScrollCallback(m_Window, OnMouseScroll);
	}

	void PollEvents()
	{
		m_MouseLastPosition = m_MousePosition;
		m_MouseScroll = { 0, 0 };
		glfwPollEvents();
	}

	void ClearEvents()
	{
		for (auto& it : m_KeyMap)
		{
			it.second.down = false;
			it.second.up = false;
		}
	}

	bool IsKey(KeyCode key)
	{
		return m_KeyMap[key].pressed;
	}

	bool IsKeyDown(KeyCode key)
	{
		if (!m_KeyMap[key].down)
			return false;

		return true;
	}

	bool IsKeyUp(KeyCode key)
	{
		if (!m_KeyMap[key].up)
			return false;

		return true;
	}
	
	Vector2& GetMousePosition()
	{
		return m_MousePosition;
	}

	Vector2& GetMouseDelta()
	{
		m_MouseDelta.x = m_MousePosition.x - m_MouseLastPosition.x;
		m_MouseDelta.y = m_MousePosition.y - m_MouseLastPosition.y;

		return m_MouseDelta;
	}

	Vector2& GetMouseScroll()
	{
		return m_MouseScroll;
	}

	void SetCursorLock(const bool lock)
	{
		m_IsCursorLocked = lock;

		if (lock)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}

	const bool IsCursorLocked()
	{
		return m_IsCursorLocked;
	}
}