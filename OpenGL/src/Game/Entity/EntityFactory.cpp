#include "EntityFactory.h"
#include "../../Core/ModelManager.h"

std::unique_ptr<ChestEntity> EntityFactory::CreateChest(glm::vec3 Position, glm::vec3 Scale, float rotationAngle, glm::vec3 rotationAxis)
{
	glm::vec3 baseHitboxSize(2.0f, 1.3f, 1.0f);
	return std::make_unique<ChestEntity>(std::make_shared<Model>(ModelManager::chestModel), Position, Scale,
		std::make_unique<Hitbox>(glm::vec3(0.f, 0.f, 0.f), baseHitboxSize * Scale), rotationAngle, rotationAxis
	);
}

std::unique_ptr<CoinEntity> EntityFactory::CreatePileCoins(glm::vec3 Position, glm::vec3 Scale, CoinType coinType)
{
	Model* model = &ModelManager::goldenCoinModel;
	if (coinType == SILVER)
	{
		model = &ModelManager::silverCoinModel;
	}
	glm::vec3 baseHitboxSize(0.4f, .1f, 0.4f);
	return std::make_unique<CoinEntity>(std::make_shared<Model>(*model), Position, Scale,
		std::make_unique<Hitbox>(glm::vec3(0.f, 0.f, 0.f), baseHitboxSize * Scale), coinType
	);
}

std::unique_ptr<ZombieEntity> EntityFactory::CreateBasicZombie(glm::vec3 Position, glm::vec3 Scale, float rotationAngle, glm::vec3 rotationAxis)
{
	glm::vec3 baseHitboxSize(0.5f, 2.5f, 0.5f);
	return std::make_unique<ZombieEntity>(std::make_shared<Model>(ModelManager::zombieModel), Position, Scale,
		std::make_unique<Hitbox>(glm::vec3(-0.12f, 1.6f, 0.f) * Scale, baseHitboxSize * Scale), rotationAngle, rotationAxis
	);
}

std::unique_ptr<LightEntity> EntityFactory::CreateLightEntity(glm::vec3 Position, glm::vec3 Scale)
{
	glm::vec3 baseHitboxSize(1.f);
	PointLight pointLight(
		Position + glm::vec3(0.f, 1.f, .0f),
		1.0f, 0.027f, 0.0028f,
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.8f, 0.8f, 0.8f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	return std::make_unique<LightEntity>(std::make_shared<Model>(ModelManager::bonfireModel), Position, Scale,
		std::make_unique<Hitbox>(glm::vec3(0.3f, 0.f, 0.0f) * Scale, baseHitboxSize * Scale),
		pointLight
	);
}
