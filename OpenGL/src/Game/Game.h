#pragma once
#include<vector>
#include "Player.h"
#include "Entity/Entity.h"
#include "Entity/Lights/LightEntity.h"
#include "Map/Map.h"

class Game
{
private:
	Player player;
	static std::vector<std::unique_ptr<Entity>> entities;
	static std::vector<std::unique_ptr<LightEntity>> lightsEntities;
	static std::vector<std::unique_ptr<Entity>> entitiesToAdd;
	Map map;
	void RenderLights(Shader& shader, const Camera& camera);
	void ConfigFlashLights(Shader& shader, const Camera& camera);
	void HandlePlayerInteraction(Entity& entity);
public:
	Game();
	static Player& GetPlayer();
	void Render();
	void Update(float deltaTime);
	static void SpawnSilverCoin(glm::vec3 Postion);
	~Game();
};
