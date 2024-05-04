#include "ProcessInput.h"

//Zoom
float ProcessInput::zoomLevel = 1.0f, ProcessInput::initialFov = 60.0f, ProcessInput::fov = 60.0;
const float ProcessInput::zoomSpeed = 0.4f, ProcessInput::minZoom = 0.1f,
ProcessInput::maxZoom = 10.0f, ProcessInput::minFov = 10.0f, ProcessInput::maxFov = 170.0;

int ProcessInput::usetexture = 0;
int ProcessInput::conditionIndex = 0;
int ProcessInput::useSkybox = 0;
DrawingMode ProcessInput::Current_DrawingMode = DrawingMode::FilledTriangle;

void ProcessInput::processInput(sf::RenderWindow& window, glm::vec3& cameraPosition, glm::vec3& cameraFront, glm::vec3& cameraRight, glm::vec3& cameraUp,
	const float& cameraSpeed, const float& sensitivity, float& yaws, float& pitchs, bool& firstMouse, float& lastX, float& lastY, float& deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			processMouseMovement(event, firstMouse, lastX, lastY, sensitivity, yaws, pitchs, cameraFront, cameraRight, cameraUp);
			break;
		case sf::Event::MouseWheelScrolled:
			processMouseScroll(event, zoomLevel, zoomSpeed, minZoom, maxZoom, initialFov, fov, minFov, maxFov);
			break;

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				Current_DrawingMode = DrawingMode::Points;
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				Current_DrawingMode = DrawingMode::Lines;
			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				Current_DrawingMode = DrawingMode::FilledTriangle;
			}
			break;
		}
		}

		if (event.key.code == sf::Keyboard::T && event.type == sf::Event::KeyPressed) {
			GLuint usetextureLocation = glGetUniformLocation(programIDs[TEXTURES], "usetexture");

			usetexture++;
			if (usetexture == 3)
				usetexture = 0;

			glUseProgram(programIDs[ShaderPrograms::TEXTURES]);
			glUniform1i(usetextureLocation, usetexture);
			glUseProgram(0);
		}

		if (event.key.code == sf::Keyboard::C && event.type == sf::Event::KeyPressed) {
			conditionIndex++;

			if (conditionIndex == 5)
				conditionIndex = 0;

			//std::cout << std::endl << "conditionIndex: " << conditionIndex << std::endl;

			glUseProgram(programIDs[ShaderPrograms::LIGHT]);

			GLuint useConditionIndex = glGetUniformLocation(programIDs[ShaderPrograms::LIGHT], "conditionIndex");
			glUniform1i(useConditionIndex, conditionIndex);

			glUseProgram(0);
		}

		if (event.key.code == sf::Keyboard::Z && event.type == sf::Event::KeyPressed) {
			useSkybox++;

			if (useSkybox == 4)
				useSkybox = 0;

			//std::cout << std::endl << "useSkybox: " << useSkybox << std::endl;

			glUseProgram(programIDs[ShaderPrograms::SKYBOX]);
			GLuint useConditionIndexSkybox = glGetUniformLocation(programIDs[ShaderPrograms::SKYBOX], "useSkybox");
			glUniform1i(useConditionIndexSkybox, useSkybox);

			glUseProgram(programIDs[ShaderPrograms::REFLECTION]);
			GLuint useConditionIndexReflection = glGetUniformLocation(programIDs[ShaderPrograms::REFLECTION], "useSkybox");
			glUniform1i(useConditionIndexReflection, useSkybox);

			glUseProgram(programIDs[ShaderPrograms::REFRACTION]);
			GLuint useConditionIndexRefraction = glGetUniformLocation(programIDs[ShaderPrograms::REFRACTION], "useSkybox");
			glUniform1i(useConditionIndexRefraction, useSkybox);

			glUseProgram(0);
		}
	}

	processKeyboardInput(cameraPosition, cameraFront, cameraUp, cameraSpeed, deltaTime);
}

void ProcessInput::processKeyboardInput(glm::vec3& cameraPosition, const glm::vec3& cameraFront,
	const glm::vec3& cameraUp, const float& cameraSpeed, float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		cameraPosition += (cameraSpeed * deltaTime) * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		cameraPosition -= (cameraSpeed * deltaTime) * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed * deltaTime);
	}
}

void ProcessInput::processMouseMovement(const sf::Event& event, bool& firstMouse, float& lastX, float& lastY, const float& sensitivity,
	float& yaws, float& pitchs, glm::vec3& cameraFront, glm::vec3& cameraRight, glm::vec3& cameraUp)
{
	if (firstMouse) {
		sf::Vector2i initialMousePos = sf::Mouse::getPosition();
		lastX = static_cast<float>(initialMousePos.x);
		lastY = static_cast<float>(initialMousePos.y);
		firstMouse = false;
	}

	sf::Vector2i currentMousePos = sf::Mouse::getPosition();

	float xOffset = static_cast<float>(currentMousePos.x) - lastX;
	float yOffset = lastY - static_cast<float>(currentMousePos.y);

	lastX = static_cast<float>(currentMousePos.x);
	lastY = static_cast<float>(currentMousePos.y);

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaws += xOffset;
	pitchs += yOffset;

	// pitch is out of bounds
	if (pitchs > 89.0f) {
		pitchs = 89.0f;
	}
	if (pitchs < -89.0f) {
		pitchs = -89.0f;
	}

	// Update the Euler angles
	glm::vec3 front;
	front.x = cos(glm::radians(yaws)) * cos(glm::radians(pitchs));
	front.y = sin(glm::radians(pitchs));
	front.z = sin(glm::radians(yaws)) * cos(glm::radians(pitchs));
	cameraFront = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void ProcessInput::processMouseScroll(const sf::Event& event, float& zoomLevel, const float& zoomSpeed,
	const float& minZoom, const float& maxZoom, const float& initialFov, float& fov, const float& minFov, const float& maxFov)
{
	if (event.mouseWheelScroll.delta > 0)
		zoomLevel *= exp(-zoomSpeed * 0.1f);
	else if (event.mouseWheelScroll.delta < 0)
		zoomLevel *= exp(zoomSpeed * 0.1f);

	zoomLevel = glm::clamp(zoomLevel, minZoom, maxZoom);

	//std::cout << "initialFov: " << initialFov << " | zoomLevel: " << zoomLevel;

	fov = initialFov * zoomLevel;
	fov = glm::clamp(fov, minFov, maxFov);

	//std::cout << " | fov: " << fov << std::endl;
}