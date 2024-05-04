#pragma once
#include "../Main.h"
#include "../Vertex.h"

class Shapes
{
#pragma region Cube
	static GLuint IBO_Cube, VBO_Cube;
	static vertex  cube_core_vertices[];
#pragma endregion Cube

#pragma region Prism
	static GLuint IBO_Prism, VBO_Prism;
	static vertex prism_core_vertices[];
#pragma endregion Prism

#pragma region Sphere

	static GLuint VBO_Sphere;
	static glm::vec3 Sphere_Core_vertices[4];

	static void Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);

	static void dividTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int itertions);

#pragma endregion Sphere

public:

	static void CreateCube();
	static void BindCube();

	static void CreatePrism();
	static void BindPrism();

	static std::vector<vertex> sphere_vertices;
	static void CreateSphere(int iterations);
	static void BindSphere();
};
