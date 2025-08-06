#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class CoreOpenGL
{
public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void Update();
	static void Terminate();
	static void Init(int width, int height);
	static GLFWwindow* GetGLFWwindow();
	static bool WindowShouldClose();
	static void SwapBuffers();

private:
	static GLFWwindow* window;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};