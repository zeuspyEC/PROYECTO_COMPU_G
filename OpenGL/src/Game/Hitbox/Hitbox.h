#pragma once
#include <glad/glad.h>
#include "learnopengl/shader_m.h"
#include "learnopengl/camera.h"
#include <vector>

class Hitbox
{
private:
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
	std::vector<float> vertices = {
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		4, 0, 3, 4, 3, 7,
		1, 5, 6, 1, 6, 2,
		4, 5, 1, 4, 1, 0,
		3, 2, 6, 3, 6, 7
	};
	bool isHitboxTargeted = false;
	void InitHibox();
	glm::vec3 PositionOffset;
	glm::vec3 Scale;
public:
	Hitbox(glm::vec3 positionOffset = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	~Hitbox();
	void Render(Shader& shader, const Camera& camera, const glm::vec3& position , float rotationAngle_ = 0.f,
		glm::vec3 rotationAxis_ = glm::vec3(0));
	void Update(const Camera& camera, const glm::vec3& position);
	bool IsHitboxTargeted();
	void SetHitboxTargeted(bool b);
};
