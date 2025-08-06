#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#include "glad/glad.h"
#include "learnopengl/camera.h"
#include "learnopengl/shader_m.h"
#include "learnopengl/model.h"
#include "Entity/ActionType.h"
#include "Entity/Entity.h"

class Entity;

class Player
{
private:
	Camera camera;
	Model* gunModel;
	float fireRate = 0.5f;
	float timeSinceLastShot = 0.0f;
	int health = 100; // Vida del jugador
	unsigned int healthVAO, healthVBO; // Buffers para la barra de vida
	void InitHealthBar(); // Inicialización de la barra de vida
	Shader healthShader; // Shader para la barra de vida
public:
	Player(glm::vec3 Position);
	void Update(float deltaTime);
	void Render(Shader& shader);
	Camera& GetCamera();
	bool IsShooting();
	void InteractEntity(Entity& entity, ActionType actionType);
	bool IsUsingFlashlight();
	bool IsInteracting();
	void TakeDamage(int amount);
	int GetHealth() const;
	void RenderHealthBar(Shader& shader);
	glm::vec3 GetPosition() const; // Add this line
};

#endif 