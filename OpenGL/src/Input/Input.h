#pragma once

#include <iostream>
#include "../API/OpenGL/CoreOpenGL.h"
#include "unordered_map"

class Input
{
public:
	static void Init();
	static void Update();
	static bool GetKey(int key);
	static bool GetKeyPressed(int key);
	static void SetKeyPressed(int key, bool b);
	static float xoffset;
	static float yoffset;
	static bool MouseMoved;
	static bool LeftMouseButtonPressed;

private:
	static std::unordered_map<int, bool> keys;
	static std::unordered_map<int, bool> pressedKey;
	static bool firstMouse;
	static float lastX;
	static float lastY;
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};