#include "Input.h"
#include <vector>

bool Input::firstMouse = true;
float Input::lastX;
float Input::lastY;
float Input::xoffset;
float Input::yoffset;
bool Input::MouseMoved = false;
bool Input::LeftMouseButtonPressed = false;
std::unordered_map<int, bool> Input::keys;
std::unordered_map<int, bool> Input::pressedKey;

void Input::Init()
{
	GLFWwindow* window = CoreOpenGL::GetGLFWwindow();
	if (!window)
	{
		exit(-2);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool Input::GetKey(int key)
{
	return keys[key];
}

bool Input::GetKeyPressed(int key)
{
	return pressedKey[key];
}

void Input::SetKeyPressed(int key, bool b)
{
	pressedKey[key] = b;
}

void Input::Update()
{
	if (GetKey(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(CoreOpenGL::GetGLFWwindow(), true);
	}
}

void Input::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	MouseMoved = true;
}

void  Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			LeftMouseButtonPressed = true;
		}
		else if (action == GLFW_RELEASE) {
			LeftMouseButtonPressed = false;
		}
	}
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}

	if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}

	if (action == GLFW_PRESS)
	{
		pressedKey[key] = !pressedKey[key];
	}
}
