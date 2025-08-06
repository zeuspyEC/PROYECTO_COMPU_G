#pragma once
#include "../Entity.h"

struct PointLight {
	glm::vec3 position;
	float constant, linear, quadratic;
	glm::vec3 ambient, diffuse, specular;

	PointLight(glm::vec3 pos, float c, float l, float q,
		glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
		: position(pos), constant(c), linear(l), quadratic(q),
		ambient(amb), diffuse(diff), specular(spec) {}
};

class LightEntity : public Entity
{
private:
	int NumLight = 0;
	bool isLightDestroyed = false;
public:
	PointLight pointLight;
	LightEntity(const std::shared_ptr<Model>& model, glm::vec3 position, glm::vec3 scale, std::unique_ptr<Hitbox> hitbox_, PointLight pointLight);
	void Render(Shader& shader, const Camera& camera) override;
	void Update(float deltaTime, const Camera& camera) override;
	void Interact(Player& player, ActionType  actionType) override;
	void SetNumLight(int num) { NumLight = num; };
	bool IsLightActive() { return !isLightDestroyed; };
};