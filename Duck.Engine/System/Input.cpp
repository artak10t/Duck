#include "input.h"
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Duck::Input
{
	static GLFWwindow* glfw_window = nullptr;

	// Keyboard
	struct KeyState
	{
		bool down = false;
		bool pressed = false;
		bool up = false;
	};
	static std::unordered_map<int, KeyState> keyMap = {};


	//Mouse
	static bool isCursorLocked = false;
	static Vector2 mouseLastPosition = { 0, 0 };
	static Vector2 mouseDelta = { 0, 0 };
	static Vector2 mousePosition = { 0, 0 };
	static Vector2 mouseScroll = { 0, 0 };

	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			keyMap[key].down = true;
			keyMap[key].pressed = true;
			keyMap[key].up = false;
			break;
		case GLFW_RELEASE:
			keyMap[key].down = false;
			keyMap[key].pressed = false;
			keyMap[key].up = true;
			break;
		}
	}

	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		OnKey(window, button, -1, action, mods);
	}

	static void OnMousePosition(GLFWwindow* window, double x, double y)
	{
		mousePosition.x = static_cast<float>(x);
		mousePosition.y = static_cast<float>(y);
	}

	static void OnMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
	{
		mouseScroll.x = static_cast<float>(deltaX);
		mouseScroll.y = static_cast<float>(deltaY);
	}

	void Init()
	{
		glfw_window = glfwGetCurrentContext();

		assert(glfw_window != NULL);

		glfwSetKeyCallback(glfw_window, OnKey);
		glfwSetMouseButtonCallback(glfw_window, OnMouseButton);
		glfwSetCursorPosCallback(glfw_window, OnMousePosition);
		glfwSetScrollCallback(glfw_window, OnMouseScroll);
	}

	void PollEvents()
	{
		mouseLastPosition = mousePosition;
		mouseScroll = { 0, 0 };
		glfwPollEvents();
	}

	void ClearEvents()
	{
		for (auto& it : keyMap)
		{
			it.second.down = false;
			it.second.up = false;
		}
	}

	bool GetKey(KeyCode key)
	{
		return keyMap[key].pressed;
	}

	bool GetKeyDown(KeyCode key)
	{
		if (!keyMap[key].down)
			return false;

		return true;
	}

	bool GetKeyUp(KeyCode key)
	{
		if (!keyMap[key].up)
			return false;

		return true;
	}
	
	Vector2& GetMousePosition()
	{
		return mousePosition;
	}

	Vector2& GetMouseDelta()
	{
		mouseDelta.x = mousePosition.x - mouseLastPosition.x;
		mouseDelta.y = mousePosition.y - mouseLastPosition.y;

		return mouseDelta;
	}

	Vector2& GetMouseScroll()
	{
		return mouseScroll;
	}

	void SetCursorLock(const bool lock)
	{
		isCursorLocked = lock;

		if (lock)
		{
			glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}

	const bool GetCursorLocked()
	{
		return isCursorLocked;
	}
}