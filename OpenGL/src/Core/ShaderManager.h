#pragma once

#include <learnopengl/shader_m.h>

class ShaderManager
{
public:
	static Shader HitboxShader;
	static Shader LightShader;
	static Shader LightShaderNoFlash;
	static void Init();
};

