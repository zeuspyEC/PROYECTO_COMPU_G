#include "ShaderManager.h"

Shader ShaderManager::HitboxShader;
Shader ShaderManager::LightShader;
Shader ShaderManager::LightShaderNoFlash;

void ShaderManager::Init()
{
	HitboxShader = Shader("res/shaders/hitbox_shader.vs", "res/shaders/hitbox_shader.fs");
	LightShader = Shader("res/shaders/6.multiple_lights.vs", "res/shaders/6.multiple_lights.fs");
	LightShaderNoFlash = Shader("res/shaders/lightswithoutflash.vs", "res/shaders/lightswithoutflash.fs");
}
	