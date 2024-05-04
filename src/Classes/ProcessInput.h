#pragma once
#include "../Main.h"

enum DrawingMode
{
	Points,
	Lines,
	FilledTriangle
};

class ProcessInput
{
	static int conditionIndex;
	static int usetexture;
	static int useSkybox;

public:

	//Zoom
	static float zoomLevel, initialFov, fov;

	static const float
		zoomSpeed, minZoom,
		maxZoom, minFov, maxFov;

	static DrawingMode Current_DrawingMode;

	static void processInput(sf::RenderWindow& window, glm::vec3& cameraPosition, glm::vec3& cameraFront, glm::vec3& cameraRight, glm::vec3& cameraUp,
		const float& cameraSpeed, const float& sensitivity, float& yaws, float& pitchs, bool& firstMouse, float& lastX, float& lastY, float& deltaTime);

	static void processKeyboardInput(glm::vec3& cameraPosition, const glm::vec3& cameraFront,
		const glm::vec3& cameraUp, const float& cameraSpeed, float& deltaTime);

	static void processMouseMovement(const sf::Event& event, bool& firstMouse, float& lastX, float& lastY, const float& sensitivity,
		float& yaws, float& pitchs, glm::vec3& cameraFront, glm::vec3& cameraRight, glm::vec3& cameraUp);

	static void processMouseScroll(const sf::Event& event, float& zoomLevel, const float& zoomSpeed,
		const float& minZoom, const float& maxZoom, const float& initialFov, float& fov, const float& minFov, const float& maxFov);
};
