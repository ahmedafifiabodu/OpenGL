#pragma once
#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/glm\glm.hpp>
#include <gl/glm\gtc\type_ptr.hpp>
#include <gl/glm\gtx\transform.hpp>

#include "Classes/ProcessInput.h"
#include "Classes/Shapes.h"
#include "Classes/DrawHuman.h"
#include "Classes/Skybox.h"

const GLint WIDTH = 1000, HEIGHT = 1000;

const int NUM_SHADER_PROGRAMS = 7;
const std::string UV_GRID_FILE = "src/UV_Grid.jpg";
const std::string UV_GRID_FILE2 = "src/UV_Grid2.jpg";

enum ShaderPrograms {
	BASIC,
	LIGHT,
	SKYBOX,
	TEXTURES,
	REFLECTION,
	REFRACTION,
	TEXTURES2
};

extern std::vector<GLuint> programIDs;
extern std::vector<GLuint> modelMatLocs;
extern std::vector<GLuint> projMatLocs;

static void updateViewMatrix(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp) {
	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	glm::vec3 cameraPositionValue = -glm::vec3(view[3]);

	for (int i = 0; i < NUM_SHADER_PROGRAMS; ++i) {
		glUseProgram(programIDs[i]);

		GLint viewLocation = glGetUniformLocation(programIDs[i], "viewMat");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		switch (i) {
		case LIGHT:
			glUniform3fv(glGetUniformLocation(programIDs[i], "camera_position"), 1, glm::value_ptr(cameraPositionValue));
			glUniform3fv(glGetUniformLocation(programIDs[i], "light_direction"), 1, glm::value_ptr(cameraPositionValue));
			break;

		case REFLECTION:
		case REFRACTION:
			glUniform3fv(glGetUniformLocation(programIDs[i], "camera_position"), 1, glm::value_ptr(cameraPositionValue));
			break;

		default:
			break;
		}
	}
}