#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "ZombieEntity.h"
#include "../../Game.h"

ZombieEntity::ZombieEntity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale,
    std::unique_ptr<Hitbox> hitbox_,
    float rotationAngle_,
    glm::vec3 rotationAxis_)
    : Entity(model, position, scale, std::move(hitbox_), rotationAngle_, rotationAxis_)
{
}

void ZombieEntity::Render(Shader& shader, const Camera& camera)
{
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)*camera.WINDOW_WIDTH / (float)*camera.WINDOW_HEIGHT, 0.1f, 200.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    if (rotationAngle != 0)
    {
        model = glm::rotate(model, glm::radians(rotationAngle), RotationAxis);
    }
    model = glm::scale(model, Scale);
    shader.setMat4("model", model);
    objectModel->Draw(shader);

    if (Input::GetKeyPressed(GLFW_KEY_F2))
    {
        hitbox->Render(ShaderManager::HitboxShader, camera, Position);
    }
}

void ZombieEntity::Update(float deltaTime, const Camera& camera)
{
    if (life <= 0)
    {
        isActive = false;
        Game::SpawnSilverCoin(Position);
        return;
    }

    // Actualizar el cooldown del ataque
    if (currentAttackCooldown > 0)
    {
        currentAttackCooldown -= deltaTime;
    }

    glm::vec3 playerPosition = camera.Position;
    float distanceToPlayer = CalculateDistanceToPlayer(playerPosition);

    // Si el jugador está dentro del rango de detección
    if (distanceToPlayer <= detectionRange)
    {
        // Actualizar la rotación para mirar al jugador
        UpdateRotation(playerPosition);

        // Si no está en rango de ataque, moverse hacia el jugador
        if (distanceToPlayer > attackRange)
        {
            MoveTowardsPlayer(playerPosition, deltaTime);
        }
        // Si está en rango de ataque y el cooldown terminó
        else if (currentAttackCooldown <= 0)
        {
            // Aquí se implementaría la lógica de ataque
            currentAttackCooldown = attackCooldown;
        }
    }

    hitbox->Update(camera, Position);
}

void ZombieEntity::MoveTowardsPlayer(const glm::vec3& playerPosition, float deltaTime)
{
    glm::vec3 direction = playerPosition - Position;
    direction.y = 0; // Mantener la altura constante

    // Normalizar la dirección solo si no es un vector nulo
    if (glm::length(direction) > 0.0001f)
    {
        direction = glm::normalize(direction);
        Position += direction * movementSpeed * deltaTime;
    }
}

void ZombieEntity::UpdateRotation(const glm::vec3& playerPosition)
{
    glm::vec3 direction = playerPosition - Position;
    direction.y = 0; // Mantener la rotación solo en el plano horizontal

    // Usar atan2 para calcular el ángulo
    float angle = atan2(direction.x, direction.z);
    rotationAngle = glm::degrees(angle);
    RotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
}

float ZombieEntity::CalculateDistanceToPlayer(const glm::vec3& playerPosition)
{
    glm::vec3 diff = playerPosition - Position;
    return sqrt(diff.x * diff.x + diff.z * diff.z); // Solo considerar distancia horizontal
}

void ZombieEntity::Interact(Player& player, ActionType actionType)
{
    if (actionType == SHOOT)
    {
        life -= 50;
        std::cout << "Zombie life: " << life << std::endl;
        return;
    }
    if (actionType == USE)
        return;
}