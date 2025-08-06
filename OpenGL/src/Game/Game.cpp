#include "Game.h"
#include "Entity/EntityFactory.h"
#include "../Core/ShaderManager.h"
#include "../Core/ModelManager.h"
#include "../Input/Input.h"


std::vector<std::unique_ptr<Entity>> Game::entities;
std::vector<std::unique_ptr<LightEntity>> Game::lightsEntities;
std::vector<std::unique_ptr<Entity>> Game::entitiesToAdd;

Game::Game() : player(Player(glm::vec3(0.f, 20.0f, 180.0f))), map(Map())
{
	//Chest
	entities.push_back(
		EntityFactory::CreateChest(glm::vec3(-16.f, 1.7f, 142.0f), glm::vec3(3))
	);

	entities.push_back(
		EntityFactory::CreateChest(glm::vec3(-27.f, 2.5f, -21.0f), glm::vec3(6) , 90 , glm::vec3(0.f,1.0f,.0f))
	);

	entities.push_back(
		EntityFactory::CreateChest(glm::vec3(-84.f, 28.7f, -134.0f), glm::vec3(9))
	);

	entities.push_back(
		EntityFactory::CreateChest(glm::vec3(-71.f, 27.7f, -134.0f), glm::vec3(7))
	);

	entities.push_back(
		EntityFactory::CreateChest(glm::vec3(-99.f, 27.7f, -134.0f), glm::vec3(7))
	);


	//Coin
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-24.f, .0f, 180.f), glm::vec3(10), GOLD)
	);

	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-22.f, .0f, 180.f), glm::vec3(7), GOLD)
	);

	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(24.f, .0f, 160.f), glm::vec3(17), GOLD)
	);

	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-16.f, .0f, 145.0f), glm::vec3(17), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-14.f, .0f, 145.0f), glm::vec3(17), GOLD)
	);


	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-25.f, .0f, 28.0f), glm::vec3(30), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-25.f, .0f, 20.0f), glm::vec3(18), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-20.f, .0f, 24.0f), glm::vec3(12), GOLD)
	);

	//up-left
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-84.f, 24.0f, -120.0f), glm::vec3(30), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-84.f, 24.0f, -110.0f), glm::vec3(25), GOLD)
	);

	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-70.f, 24.0f, -110.0f), glm::vec3(22), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-94.f, 24.0f, -110.0f), glm::vec3(27), GOLD)
	);
	entities.push_back(
		EntityFactory::CreatePileCoins(glm::vec3(-84.f, 24.0f, -105.0f), glm::vec3(26), GOLD)
	);

	//Zombie
	entities.push_back(
		EntityFactory::CreateBasicZombie(glm::vec3(-5.0f, .0f, -5.0f), glm::vec3(3), 90, glm::vec3(0.f, 1.0f, .0f))
	);
	entities.push_back(
		EntityFactory::CreateBasicZombie(glm::vec3(6.0f, .0f, -5.0f), glm::vec3(4), -90, glm::vec3(0.f, 1.0f, .0f))
	);
	entities.push_back(
		EntityFactory::CreateBasicZombie(glm::vec3(1.0f, .0f, -10.0f), glm::vec3(5.5))
	);

	//Bonfire
	lightsEntities.push_back(
		EntityFactory::CreateLightEntity(glm::vec3(0.f, 0.f, -5.0f), glm::vec3(5))
	);

	lightsEntities.push_back(
		EntityFactory::CreateLightEntity(glm::vec3(105.f, 0.f, -4.0f), glm::vec3(7))
	);


}

void Game::Render()
{
	Shader* shader = &ShaderManager::LightShader;
	if (player.IsUsingFlashlight())
	{
		ConfigFlashLights(*shader, player.GetCamera());
	}
	else
	{
		shader = &ShaderManager::LightShaderNoFlash;
	}

	player.Render(*shader);
	RenderLights(*shader, player.GetCamera());
	for (auto& entity : entities)
	{
		if (!entity->IsEntityActive())
			continue;

		entity->Render(*shader, player.GetCamera());
	}
	map.Render(*shader, player.GetCamera());
}

void Game::Update(float deltaTime)
{
	player.Update(deltaTime);

	for (auto it = entities.begin(); it != entities.end();)
	{
		auto& entity = *it;

		if (!entity->IsEntityActive()) {
			it = entities.erase(it);
			continue;
		}

		if (entity->IsObjectHitboxTargeted()) {
			HandlePlayerInteraction(*entity);
		}
		entity->Update(deltaTime, player.GetCamera());

		++it;
	}

	entities.insert(entities.end(), std::make_move_iterator(entitiesToAdd.begin()), std::make_move_iterator(entitiesToAdd.end()));
	entitiesToAdd.clear();

	for (auto& entity : lightsEntities)
	{
		if (!entity->IsEntityActive())
			continue;

		entity->Update(deltaTime, player.GetCamera());
		if (entity->IsObjectHitboxTargeted())
		{
			HandlePlayerInteraction(*entity);
		}
	}
}


void Game::RenderLights(Shader& shader, const Camera& camera)
{
	shader.setVec3("viewPos", camera.Position);
	shader.setFloat("material.shininess", 32.0f);

	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.03f, 0.03f, 0.03f);
	shader.setVec3("dirLight.diffuse", 0.3f, 0.3f, 0.3f);
	shader.setVec3("dirLight.specular", 0.9f, 0.9f, 0.9f);

	int numOfLights = 0;
	for (auto& entity : lightsEntities)
	{
		if (entity->IsLightActive())
			numOfLights++;
	}
	shader.setInt("numOfLights", numOfLights);

	for (auto& entity : lightsEntities)
	{
		if (!entity->IsEntityActive())
			continue;

		if (entity->IsLightActive())
			entity->SetNumLight(--numOfLights);

		entity->Render(shader, camera);
	}
}

void Game::ConfigFlashLights(Shader& shader, const Camera& camera)
{
	shader.setVec3("spotLight.position", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.022f);
	shader.setFloat("spotLight.quadratic", 0.0019f);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}


void Game::HandlePlayerInteraction(Entity& entity)
{
	if (player.IsShooting())
	{
		player.InteractEntity(entity, SHOOT);
	}

	if (player.IsInteracting())
	{
		player.InteractEntity(entity, USE);
	}
}


void Game::SpawnSilverCoin(glm::vec3 Postion) {
	entitiesToAdd.push_back(
		EntityFactory::CreatePileCoins(Postion, glm::vec3(10), SILVER)
	);
}

Player& Game::GetPlayer() {
	static Game instance; // Asegurar que existe una instancia
	return instance.player;
}

Game::~Game()
{

}