#pragma once

class Engine
{
private:
	static float deltaTime;
	static float lastFrame;
	static void Shutdown();
public:
	static void Run();
};