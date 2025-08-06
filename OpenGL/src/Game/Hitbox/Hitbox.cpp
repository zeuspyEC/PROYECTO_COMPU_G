#include "Hitbox.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Hitbox::Hitbox(glm::vec3 positionOffset, glm::vec3 scale)
	: PositionOffset(positionOffset), Scale(scale)
{
	InitHibox();
}


void Hitbox::InitHibox()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Hitbox::Render(Shader& shader, const Camera& camera, const glm::vec3& position, float rotationAngle_,
	glm::vec3 rotationAxis_)
{
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(*camera.WINDOW_WIDTH) / static_cast<float>(*camera.WINDOW_HEIGHT), 0.1f, 200.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	shader.setBool("isTargeted", isHitboxTargeted);


	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, position + PositionOffset);
	if (rotationAngle_ != 0)
	{
		model = glm::rotate(model, glm::radians(rotationAngle_), rotationAxis_);
	}
	model = glm::scale(model, Scale);
	shader.setMat4("model", model);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void Hitbox::Update(const Camera& camera, const glm::vec3& position)
{
	glm::vec3 rayOrigin = camera.Position;
	glm::vec3 rayDirection = glm::normalize(camera.Front);

	glm::vec3 min = position + PositionOffset - Scale * 0.5f;
	glm::vec3 max = position + PositionOffset + Scale * 0.5f;

	float tmin = (min.x - rayOrigin.x) / rayDirection.x;
	float tmax = (max.x - rayOrigin.x) / rayDirection.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (min.y - rayOrigin.y) / rayDirection.y;
	float tymax = (max.y - rayOrigin.y) / rayDirection.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
	{
		isHitboxTargeted = false;
		return;
	}

	tmin = std::max(tmin, tymin);
	tmax = std::min(tmax, tymax);

	float tzmin = (min.z - rayOrigin.z) / rayDirection.z;
	float tzmax = (max.z - rayOrigin.z) / rayDirection.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		isHitboxTargeted = false;
		return;
	}

	isHitboxTargeted = true;
}

void Hitbox::SetHitboxTargeted(bool b)
{
	isHitboxTargeted = b;
}

bool Hitbox::IsHitboxTargeted()
{
	return isHitboxTargeted;
}

Hitbox::~Hitbox()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}