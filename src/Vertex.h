#pragma once
#include "Main.h"

class vertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;

	vertex() {}

	vertex(glm::vec3 _position, glm::vec3 _color) : position{ _position }, color{ _color }
	{
	}

	vertex(glm::vec3 _position) : position{ _position }, color(1, 1, 1)
	{
	}

	vertex(glm::vec3 _position, glm::vec3 _norm, glm::vec2 _uv) : position{ _position }, color{ _norm }, uv{ _uv }
	{
	}
};
