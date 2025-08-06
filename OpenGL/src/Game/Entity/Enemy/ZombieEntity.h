#pragma once
#include "../Entity.h"
#include "../../Player.h"

class ZombieEntity : public Entity {
public:
    ZombieEntity(std::shared_ptr<Model> model,
        glm::vec3 position,
        glm::vec3 scale,
        std::unique_ptr<Hitbox> hitbox_,
        float rotationAngle_ = 0,
        glm::vec3 rotationAxis_ = glm::vec3(0.f));

    virtual void Render(Shader& shader, const Camera& camera) override;
    virtual void Update(float deltaTime, const Camera& camera) override;
    virtual void Interact(Player& player, ActionType actionType) override;

private:
    float movementSpeed = 10.0f; // Velocidad de movimiento del zombie
    float detectionRange = 50.0f; // Rango de detección del jugador
    float attackRange = 10.0f; // Rango de ataque
    float attackCooldown = 2.0f; // Tiempo entre ataques
    float currentAttackCooldown = 0.0f; // Contador actual del cooldown
    int attackDamage = 10; // Daño que hace el zombie
    int life = 100; // Vida del zombie

    void MoveTowardsPlayer(const glm::vec3& playerPosition, float deltaTime);
    void UpdateRotation(const glm::vec3& playerPosition);
    float CalculateDistanceToPlayer(const glm::vec3& playerPosition);
};