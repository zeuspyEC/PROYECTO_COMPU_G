#include "Map.h"

Map::Map()
{
	mapModel = std::make_shared<Model>(ModelManager::dungeonModel);
}

void Map::Render(Shader& shader, const Camera& camera)
{
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)*camera.WINDOW_WIDTH / (float)*camera.WINDOW_HEIGHT, 0.1f, 200.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, Scale);
	shader.setMat4("model", model);
	mapModel->Draw(shader);
}