#include "ChestEntity.h"

ChestEntity::ChestEntity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale,
	std::unique_ptr<Hitbox> hitbox_,
	float rotationAngle_ ,
	glm::vec3 rotationAxis_ )
	: Entity(model, position, scale, std::move(hitbox_), rotationAngle_, rotationAxis_) {}

void ChestEntity::Render(Shader& shader, const Camera& camera)
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
		hitbox->Render(ShaderManager::HitboxShader, camera, Position , rotationAngle , RotationAxis);
	}
}

void ChestEntity::Update(float deltaTime, const Camera& camera)
{
	hitbox->Update(camera, Position);
}
void ChestEntity::Interact(Player& player, ActionType actionType)
{
	if (actionType == SHOOT)
	{

	}
	if (actionType == USE)
	{

	}
}
