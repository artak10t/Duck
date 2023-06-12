#include "input.h"
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Duck::Input
{
	static GLFWwindow* window = nullptr;

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

	static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
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

	static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		onKey(window, button, -1, action, mods);
	}

	static void onMousePosition(GLFWwindow* window, double x, double y)
	{
		mousePosition.x = static_cast<float>(x);
		mousePosition.y = static_cast<float>(y);
	}

	static void onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
	{
		mouseScroll.x = static_cast<float>(deltaX);
		mouseScroll.y = static_cast<float>(deltaY);
	}


	void Init()
	{
		window = glfwGetCurrentContext();

		assert(window != NULL);

		glfwSetKeyCallback(window, onKey);
		glfwSetMouseButtonCallback(window, onMouseButton);
		glfwSetCursorPosCallback(window, onMousePosition);
		glfwSetScrollCallback(window, onMouseScroll);
	}

	void PollEvents()
	{
		mouseLastPosition = mousePosition;
		mouseScroll = { 0, 0 };
		glfwPollEvents();
	}

	bool IsKeyPressed(KeyCode key)
	{
		return keyMap[key].pressed;
	}

	bool IsKeyDown(KeyCode key)
	{
		if (!keyMap[key].down)
			return false;

		keyMap[key].down = false;
		return true;
	}

	bool IsKeyUp(KeyCode key)
	{
		if (!keyMap[key].up)
			return false;

		keyMap[key].up = false;
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
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}

	const bool IsCursorLocked()
	{
		return isCursorLocked;
	}
}