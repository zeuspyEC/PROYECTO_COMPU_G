#pragma once
#include "Chest/ChestEntity.h"
#include "Coin/CoinEntity.h"
#include "Enemy/ZombieEntity.h"
#include "Lights/LightEntity.h"

class EntityFactory
{
public:
	static std::unique_ptr<ChestEntity> CreateChest(glm::vec3 Position, glm::vec3 Scale , float rotationAngle = 0.f, glm::vec3 rotationAxis = glm::vec3(0.0f));
	static std::unique_ptr<CoinEntity> CreatePileCoins(glm::vec3 Position, glm::vec3 Scale, CoinType coinType);
	static std::unique_ptr<ZombieEntity> CreateBasicZombie(glm::vec3 Position, glm::vec3 Scale, float rotationAngle = 0.f, glm::vec3 rotationAxis = glm::vec3(0.0f));
	static std::unique_ptr<LightEntity> CreateLightEntity(glm::vec3 Position, glm::vec3 Scale);
};