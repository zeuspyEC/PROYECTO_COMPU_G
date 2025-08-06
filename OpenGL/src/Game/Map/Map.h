#pragma once
#include <learnopengl/model.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include "../../Core/ModelManager.h"
#include <glm/glm.hpp>

class Map
{
private:
	glm::vec3 Scale = glm::vec3(6.f);
	std::shared_ptr<Model> mapModel;
public:
	void Render(Shader& shader, const Camera& camera);
	Map();
};
