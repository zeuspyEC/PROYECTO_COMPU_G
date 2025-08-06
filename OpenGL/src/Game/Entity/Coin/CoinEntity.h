#pragma once
#include "../Entity.h"
#include "CoinType.h"

class CoinEntity : public Entity
{
private:
	CoinType type;
public:
	CoinEntity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale, std::unique_ptr<Hitbox> hitbox_ , CoinType type);
	void Render(Shader& shader, const Camera& camera) override;
	void Update(float deltaTime, const Camera& camera) override;
	void Interact(Player& player, ActionType  actionType) override;
};
