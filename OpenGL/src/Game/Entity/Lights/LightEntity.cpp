#include "LightEntity.h"

LightEntity::LightEntity(const std::shared_ptr<Model>& model, glm::vec3 position, glm::vec3 scale,
	std::unique_ptr<Hitbox> hitbox_, PointLight pointLight)
	: Entity(model, position, scale, std::move(hitbox_)),
	pointLight(pointLight) 
{}

void LightEntity::Render(Shader& shader, const Camera& camera)
{
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)*camera.WINDOW_WIDTH / (float)*camera.WINDOW_HEIGHT, 0.1f, 200.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	if (!isLightDestroyed)
	{
		shader.setVec3("pointLights[" + std::to_string(NumLight) +"].position", pointLight.position);
		shader.setVec3("pointLights[" + std::to_string(NumLight) + "].ambient", pointLight.ambient);
		shader.setVec3("pointLights[" + std::to_string(NumLight) + "].diffuse", pointLight.diffuse);
		shader.setVec3("pointLights[" + std::to_string(NumLight) + "].specular", pointLight.specular);
		shader.setFloat("pointLights[" + std::to_string(NumLight) + "].constant", pointLight.constant);
		shader.setFloat("pointLights[" + std::to_string(NumLight) + "].linear", pointLight.linear);
		shader.setFloat("pointLights[" + std::to_string(NumLight) + "].quadratic", pointLight.quadratic);
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, Position);
	model = glm::scale(model, Scale);
	shader.setMat4("model", model);
	objectModel->Draw(shader);
	if (Input::GetKeyPressed(GLFW_KEY_F2))
	{
		hitbox->Render(ShaderManager::HitboxShader, camera, Position);
	}
}

void LightEntity::Update(float deltaTime, const Camera& camera)
{
	hitbox->Update(camera, Position);
}
void LightEntity::Interact(Player& player, ActionType actionType)
{
	if (actionType == SHOOT)
	{
		isLightDestroyed = true;
		return;
	}
	if (actionType == USE)
	{
		isLightDestroyed = false;
		return;
	}
}