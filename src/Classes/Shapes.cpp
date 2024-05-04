#include "Shapes.h"

#pragma region Cube

GLuint Shapes::IBO_Cube, Shapes::VBO_Cube;
vertex Shapes::cube_core_vertices[] = {
	// Front face
	{glm::vec3(-0.5, 0.5, 0.5),glm::vec3(1,0,0),glm::vec2(0,0)},     //1
	{glm::vec3(-0.5, -0.5, 0.5),glm::vec3(0,1,0),glm::vec2(0,1)},    //2
	{glm::vec3(0.5, -0.5, 0.5),glm::vec3(1,0,1),glm::vec2(1,1)},     //3
	{glm::vec3(0.5, 0.5, 0.5),glm::vec3(0,0,1),glm::vec2(1,0)},       //4

	// Right face
	{glm::vec3(0.5, 0.5, 0.5),glm::vec3(1,0,0),glm::vec2(0,0)},      //5
	{glm::vec3(0.5, -0.5, 0.5),glm::vec3(0,1,0),glm::vec2(0,1)},     //6
	{glm::vec3(0.5, -0.5, -0.5),glm::vec3(1,0,1),glm::vec2(1,1)},    //7
	{glm::vec3(0.5, 0.5, -0.5),glm::vec3(0,0,1),glm::vec2(1,0)},      //8

	// Back face
	{glm::vec3(0.5, 0.5, -0.5),glm::vec3(1,0,0), glm::vec2(0,0)},     //9
	{glm::vec3(0.5, -0.5, -0.5),glm::vec3(0,1,0), glm::vec2(0,1)},    //10
	{glm::vec3(-0.5, -0.5, -0.5),glm::vec3(1,0,1), glm::vec2(1,1)},   //11
	{glm::vec3(-0.5, 0.5, -0.5),glm::vec3(0,0,1), glm::vec2(1,0)},     //12

	// Left face
	{glm::vec3(-0.5, 0.5, -0.5),glm::vec3(1,0,0),glm::vec2(0,0)},     //13
	{glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0,1,0),glm::vec2(0,1)},    //14
	{glm::vec3(-0.5, -0.5, 0.5),glm::vec3(1,0,1),glm::vec2(1,1)},     //15
	{glm::vec3(-0.5, 0.5, 0.5),glm::vec3(0,0,1),glm::vec2(1,0)},       //16

	// Top face
	{glm::vec3(-0.5, 0.5, -0.5),glm::vec3(1,0,0),glm::vec2(0,0)},     //17
	{glm::vec3(-0.5, 0.5, 0.5),glm::vec3(0,1,0),glm::vec2(0,1)},      //18
	{glm::vec3(0.5, 0.5, 0.5),glm::vec3(1,0,1),glm::vec2(1,1)},       //19
	{glm::vec3(0.5, 0.5, -0.5),glm::vec3(0,0,1),glm::vec2(1,0)},      //20

	// Bottom face
	{glm::vec3(-0.5, -0.5, 0.5),glm::vec3(1,0,0),glm::vec2(0,0)},    //21
	{glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0,1,0),glm::vec2(0,1)},   //22
	{glm::vec3(0.5, -0.5, -0.5),glm::vec3(1,0,1),glm::vec2(1,1)},    //23
	{glm::vec3(0.5, -0.5, 0.5),glm::vec3(0,0,1),glm::vec2(1,0)},      //24
};

void Shapes::CreateCube() {
	int vertices_Indeces[] = {
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Right face
		4, 5, 6,
		4, 6, 7,

		// Back face
		8, 9, 10,
		8, 10, 11,

		// Left face
		12, 13, 14,
		12, 14, 15,

		// Top face
		16, 17, 18,
		16, 18, 19,

		// Bottom face
		20, 21, 22,
		20, 22, 23
	};

	//Create VBO
	glGenBuffers(1, &VBO_Cube);
	//Binding VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_core_vertices), cube_core_vertices, GL_STATIC_DRAW);

	//Create Index Buffer
	glGenBuffers(1, &IBO_Cube);
	//Binding Index Buffer
	glBindBuffer(GL_ARRAY_BUFFER, IBO_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_Indeces), vertices_Indeces, GL_STATIC_DRAW);

	//Shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}
void Shapes::BindCube()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Cube);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}

#pragma endregion Cube

#pragma region Prism

GLuint Shapes::IBO_Prism, Shapes::VBO_Prism;
vertex Shapes::prism_core_vertices[] =
{
		{glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(1,0,0)},			//0
		{glm::vec3(-1.0f, -1.0f, 1.0f),glm::vec3(0,1,0)},		//1
		{glm::vec3(1.0f, -1.0f, 1.0f),glm::vec3(0,0,1)},		//2
		{glm::vec3(1.0f, -1.0f, -1.0f),glm::vec3(1,0,0)},		//3
		{glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(0,1,0)},		//4
};

void Shapes::CreatePrism()
{
	int vertices_Indeces[] = {
	0,1,2,
	0,2,3,
	0,3,4,
	0,4,1,

	1,2,4,
	2,4,3,
	};

	//Create VBO
	glGenBuffers(1, &VBO_Prism);

	//Binding VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Prism);
	glBufferData(GL_ARRAY_BUFFER, sizeof(prism_core_vertices), prism_core_vertices, GL_STATIC_DRAW);

	//Create Index Buffer
	glGenBuffers(1, &IBO_Prism);

	//Binding Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Prism);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_Indeces), vertices_Indeces, GL_STATIC_DRAW);

	//Shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}
void Shapes::BindPrism()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Prism);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Prism);

	// Shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}

#pragma endregion Prism

#pragma region Sphere

GLuint Shapes::VBO_Sphere;
std::vector<vertex> Shapes::sphere_vertices;
glm::vec3 Shapes::Sphere_Core_vertices[4] = {
	glm::vec3(0.0, 0.0, 1.0),
	glm::vec3(0.0, 0.942809, -0.333333),
	glm::vec3(-0.816497, -0.471405, -0.333333),
	glm::vec3(0.816497, -0.471405, -0.333333)
};

void Shapes::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 normal = (a + b + c) / 3.0f;
	Shapes::sphere_vertices.push_back(vertex(a, a, glm::vec2(0, 0)));
	Shapes::sphere_vertices.push_back(vertex(b, b, glm::vec2(1, 0)));
	Shapes::sphere_vertices.push_back(vertex(c, c, glm::vec2(0, 1)));
}
void Shapes::dividTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, int itertions)
{
	if (itertions > 0)
	{
		glm::vec3 v1 = glm::normalize(a + b);
		glm::vec3 v2 = glm::normalize(a + c);
		glm::vec3 v3 = glm::normalize(b + c);

		dividTriangle(a, v1, v2, itertions - 1);
		dividTriangle(v1, b, v3, itertions - 1);
		dividTriangle(v1, v3, v2, itertions - 1);
		dividTriangle(v2, v3, c, itertions - 1);
	}
	else
	{
		Triangle(a, b, c);
	}
}
void Shapes::CreateSphere(int iterations)
{
	Shapes::sphere_vertices.clear();
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[1], Sphere_Core_vertices[2], iterations);
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[3], Sphere_Core_vertices[1], iterations);
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[2], Sphere_Core_vertices[3], iterations);
	dividTriangle(Sphere_Core_vertices[3], Sphere_Core_vertices[2], Sphere_Core_vertices[1], iterations);

	glGenBuffers(1, &VBO_Sphere);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere);
	glBufferData(GL_ARRAY_BUFFER, Shapes::sphere_vertices.size() * sizeof(vertex), Shapes::sphere_vertices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}
void Shapes::BindSphere()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
}

#pragma endregion Sphere