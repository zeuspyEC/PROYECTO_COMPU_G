#include "CoinEntity.h"

CoinEntity::CoinEntity(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale, std::unique_ptr<Hitbox> hitbox , CoinType coinType)
	: Entity(model, position, scale, std::move(hitbox) ) , type(coinType)
{}

void CoinEntity::Render(Shader& shader, const Camera& camera)
{
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)*camera.WINDOW_WIDTH / (float)*camera.WINDOW_HEIGHT, 0.1f, 200.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Position);
	model = glm::scale(model, Scale);
	shader.setMat4("model", model);
	objectModel->Draw(shader);
	if (Input::GetKeyPressed(GLFW_KEY_F2))
	{
		hitbox->Render(ShaderManager::HitboxShader, camera, Position );
	}
}

void CoinEntity::Update(float deltaTime, const Camera& camera)
{
	hitbox->Update(camera, Position);
}
void CoinEntity::Interact(Player& player, ActionType actionType)
{
	if (actionType == SHOOT)
	{
		return;
	}
	if (actionType == USE)
	{
		isActive = false;
		return;
	}
}
