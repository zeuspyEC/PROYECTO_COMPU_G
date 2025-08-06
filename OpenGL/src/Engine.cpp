#include "Engine.h"

#include "API/OpenGL/CoreOpenGL.h"
#include "Input/Input.h"
#include "Core/ShaderManager.h"
#include "Core/ModelManager.h"
#include "Game/Game.h"

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

float Engine::deltaTime = 0.0f;
float Engine::lastFrame = 0.0f;


void Engine::Run()
{
	CoreOpenGL::Init(1000, 1000);
	Input::Init();
	ShaderManager::Init();
	ModelManager::Init();
	Game game;

	while (!CoreOpenGL::WindowShouldClose())
	{

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		CoreOpenGL::Update();
		Input::Update();
		game.Update(deltaTime);
		game.Render();
		CoreOpenGL::SwapBuffers();
	}
	Shutdown();
}

void Engine::Shutdown()
{
	CoreOpenGL::Terminate();
}