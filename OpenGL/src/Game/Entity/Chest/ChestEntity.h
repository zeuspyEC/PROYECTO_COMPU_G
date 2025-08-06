#pragma once
#include "../Entity.h"

class ChestEntity : public Entity
{
public:
	ChestEntity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale, 
		std::unique_ptr<Hitbox> hitbox_, 
		float rotationAngle_ = 0.0f, 
		glm::vec3 rotationAxis_ = glm::vec3(0.0f));
	void Render(Shader& shader, const Camera& camera) override;
	void Update(float deltaTime, const Camera& camera) override;
	void Interact(Player& player, ActionType  actionType) override;
};