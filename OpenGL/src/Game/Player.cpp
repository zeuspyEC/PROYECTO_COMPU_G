#include "Player.h"
#include "../Core/ModelManager.h"
#include "../API/OpenGL/CoreOpenGL.h"
#include "../Input/Input.h"
#include "glad/glad.h"


Player::Player(glm::vec3 Position) :
	gunModel(&ModelManager::gunModel),
	camera(Camera(Position, &CoreOpenGL::SCR_WIDTH, &CoreOpenGL::SCR_HEIGHT))
{
	InitHealthBar(); // Inicializar la barra de vida
}

void Player::Render(Shader& shader)
{
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(*camera.WINDOW_WIDTH) / static_cast<float>(*camera.WINDOW_HEIGHT), 0.1f, 200.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	// render the gun model
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.45f, -0.5f, -1.5f));
	model = glm::scale(model, glm::vec3(0.03f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shader.setMat4("model", glm::inverse(camera.GetViewMatrix()) * model);
	gunModel->Draw(shader);

	RenderHealthBar(shader);
}


void Player::Update(float deltaTime)
{
	if (Input::GetKey(GLFW_KEY_W))
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (Input::GetKey(GLFW_KEY_S))
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (Input::GetKey(GLFW_KEY_A))
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (Input::GetKey(GLFW_KEY_D))
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (Input::MouseMoved)
	{
		camera.ProcessMouseMovement(Input::xoffset, Input::yoffset);
		Input::MouseMoved = false;
	}
	timeSinceLastShot += deltaTime;

	std::cout << "x: " << camera.Position.x << " y: " << camera.Position.y << " z: " << camera.Position.z << std::endl;
}

Camera& Player::GetCamera() {
	return camera;
}

bool Player::IsShooting() {
	if (Input::LeftMouseButtonPressed && timeSinceLastShot >= fireRate)
	{
		timeSinceLastShot = 0.0f;
		return true;
	}

	return false;
}

void Player::InteractEntity(Entity& entity, ActionType actionType)
{
	entity.Interact(*this, actionType);
}

bool Player::IsUsingFlashlight()
{
	return Input::GetKeyPressed(GLFW_KEY_F);
}

bool Player::IsInteracting() {
	bool b = Input::GetKeyPressed(GLFW_KEY_E);
	Input::SetKeyPressed(GLFW_KEY_E, false);
	return b;
}

void Player::TakeDamage(int amount) {
	health -= amount;
	if (health < 0) health = 0;
}

int Player::GetHealth() const {
	return health;
}

void Player::InitHealthBar()
{
	float vertices[] = {
		// Posiciones   // Colores
		-0.15f,  0.05f,  1.0f, 0.0f, 0.0f, // Izquierda abajo (Rojo)
		-0.15f,  0.10f,  1.0f, 0.0f, 0.0f, // Izquierda arriba
		 0.15f,  0.10f,  0.0f, 1.0f, 0.0f, // Derecha arriba (Verde)
		 0.15f,  0.05f,  0.0f, 1.0f, 0.0f  // Derecha abajo
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &healthVAO);
	glGenBuffers(1, &healthVBO);

	glBindVertexArray(healthVAO);
	glBindBuffer(GL_ARRAY_BUFFER, healthVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	healthShader = Shader("res/shaders/healthbar.vs", "res/shaders/healthbar.fs");
}

void Player::RenderHealthBar(Shader& shader)
{
	float healthPercentage = (float)health / 100.0f;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(healthPercentage, 1.0f, 1.0f));

	healthShader.use();
	healthShader.setMat4("model", model);

	glBindVertexArray(healthVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

// obtener la posicion de la camara
glm::vec3 Player::GetPosition() const {
	return camera.Position;
}