#include "input.h"
#include <glfw/glfw3.h>

#include "Logger.h"

namespace Duck::Input
{
	struct KeyState
	{
		bool down = false;
		bool press = false;
		bool up = false;
	};
	static std::unordered_map<int, KeyState> _keyMap = {};
	static bool _isCursorLocked = false;
	static Vector2 _mouseLastPosition = { 0, 0 };
	static Vector2 _mouseDelta = { 0, 0 };
	static Vector2 _mousePosition = { 0, 0 };
	static Vector2 _mouseScrollDelta = { 0, 0 };
	static GLFWwindow* _window = nullptr;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			_keyMap[key].down = true;
			_keyMap[key].press = true;
			_keyMap[key].up = false;
			break;
		case GLFW_RELEASE:
			_keyMap[key].down = false;
			_keyMap[key].press = false;
			_keyMap[key].up = true;
			break;
		}
	}

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		keyCallback(window, button, -1, action, mods);
	}

	static void cursorPosCallback(GLFWwindow* window, double x, double y)
	{
		_mousePosition.x = static_cast<float>(x);
		_mousePosition.y = static_cast<float>(y);
	}

	static void scrollCallback(GLFWwindow* window, double deltaX, double deltaY)
	{
		_mouseScrollDelta.x = static_cast<float>(deltaX);
		_mouseScrollDelta.y = static_cast<float>(deltaY);
	}


	void Init()
	{
		_window = glfwGetCurrentContext();

		assert(_window != NULL);

		glfwSetKeyCallback(_window, keyCallback);
		glfwSetMouseButtonCallback(_window, mouseButtonCallback);
		glfwSetCursorPosCallback(_window, cursorPosCallback);
		glfwSetScrollCallback(_window, scrollCallback);
	}

	void PollEvents()
	{
		_mouseLastPosition = _mousePosition;
		_mouseScrollDelta = { 0, 0 };
		glfwPollEvents();
	}

	bool KeyPress(KeyCode key)
	{
		return _keyMap[key].press;
	}

	bool KeyDown(KeyCode key)
	{
		if (!_keyMap[key].down)
			return false;

		_keyMap[key].down = false;
		return true;
	}

	bool KeyUp(KeyCode key)
	{
		if (!_keyMap[key].up)
			return false;

		_keyMap[key].up = false;
		return true;
	}
	
	Vector2& MousePosition()
	{
		return _mousePosition;
	}

	Vector2& MouseDelta()
	{
		_mouseDelta.x = _mousePosition.x - _mouseLastPosition.x;
		_mouseDelta.y = _mousePosition.y - _mouseLastPosition.y;

		return _mouseDelta;
	}

	Vector2& MouseScrollDelta()
	{
		return _mouseScrollDelta;
	}

	void LockCursor(const bool lock)
	{
		_isCursorLocked = lock;

		if (lock)
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}

	const bool IsCursorLocked()
	{
		return _isCursorLocked;
	}
}