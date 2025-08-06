#pragma once
#include "../Hitbox/Hitbox.h"
#include "learnopengl/model.h"
#include "glad/glad.h"
#include "../Player.h"
#include "ActionType.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Core/ShaderManager.h"
#include "../../Input/Input.h"

class Player;

class Entity
{
protected:
	std::shared_ptr<Model> objectModel;
	std::unique_ptr<Hitbox> hitbox;
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 RotationAxis;
	float rotationAngle;
	bool isActive = true;
public:
	Entity(std::shared_ptr<Model> model, 
		glm::vec3 position, 
		glm::vec3 scale,
		std::unique_ptr<Hitbox> hitbox_, 
		float rotationAngle_ = 0.0f, 
		glm::vec3 rotationAxis_ = glm::vec3(0.0f, .0f, 0.0f))
		: objectModel(model), Position(position), Scale(scale), hitbox(std::move(hitbox_)),
		RotationAxis(rotationAxis_), rotationAngle(rotationAngle_) {}
	bool IsObjectHitboxTargeted() { return hitbox->IsHitboxTargeted(); }
	bool IsEntityActive() { return isActive; }
	virtual void Render(Shader& shader, const Camera& camera) {};
	virtual void Update(float deltaTime, const Camera& camera) {};
	virtual void Interact(Player& player, ActionType  actionType) {};
	virtual ~Entity() = default;
};
