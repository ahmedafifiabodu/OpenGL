#include "Main.h"

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

GLuint TextureId_UVGrind, TextureId_UVGrind2;

std::vector<GLuint> programIDs(NUM_SHADER_PROGRAMS);
std::vector<GLuint> modelMatLocs(NUM_SHADER_PROGRAMS);
std::vector<GLuint> projMatLocs(NUM_SHADER_PROGRAMS);

static void CompileShader()
{
	std::vector<std::string> vertexShaderFiles = {
	"src/Vertex Shaders/VS.glsl",
	"src/Vertex Shaders/VS_Light.glsl",
	"src/Vertex Shaders/VS_Skybox.glsl",
	"src/Vertex Shaders/VS_Textures.glsl",
	"src/Vertex Shaders/VS_Reflection.glsl",
	"src/Vertex Shaders/VS_Refractive.glsl",
	"src/Vertex Shaders/VS_Textures.glsl"
	};

	std::vector<std::string> fragmentShaderFiles = {
		"src/Fragment Shaders/FS.glsl",
		"src/Fragment Shaders/FS_Light.glsl",
		"src/Fragment Shaders/FS_Skybox.glsl",
		"src/Fragment Shaders/FS_Textures.glsl",
		"src/Fragment Shaders/FS_Reflection.glsl",
		"src/Fragment Shaders/FS_Refractive.glsl",
		"src/Fragment Shaders/FS_Textures.glsl",
	};

	for (int i = 0; i < NUM_SHADER_PROGRAMS; ++i) {
		programIDs[i] = InitShader(vertexShaderFiles[i].c_str(), fragmentShaderFiles[i].c_str());
		glUseProgram(programIDs[i]);
		modelMatLocs[i] = glGetUniformLocation(programIDs[i], "modelMat");
		projMatLocs[i] = glGetUniformLocation(programIDs[i], "projMat");
	}
}
static int Init()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Error";
		(void)getchar();
		return 1;
	}
	else
	{
		if (GLEW_VERSION_3_0)
			std::cout << "Driver support OpenGL 3.0\nDetails:\n";
	}

	std::cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	GLenum initError = glGetError();
	if (initError != GL_NO_ERROR) {
		// Handle the error
		switch (initError) {
		case GL_INVALID_ENUM:
			// Handle invalid enum error
			std::cout << "GL_INVALID_ENUM" << std::endl;
			break;
		case GL_INVALID_VALUE:
			// Handle invalid value error
			std::cout << "GL_INVALID_VALUE" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			// Handle invalid operation error
			std::cout << "GL_INVALID_OPERATION" << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			// Handle invalid framebuffer operation error
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			// Handle out-of-memory error
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
			break;
		default:
			// Handle other errors
			std::cout << "default" << std::endl;
			break;
		}
	}

	CompileShader();

	for (int i = 0; i < NUM_SHADER_PROGRAMS; ++i) {
		glUseProgram(programIDs[i]);

		modelMatLocs[i] = glGetUniformLocation(programIDs[i], "modelMat");
		projMatLocs[i] = glGetUniformLocation(programIDs[i], "projMat");
	}

	Skybox::CreateCubeMapDesert();
	Skybox::CreateCubeMapFishPond();
	Skybox::CreateCubeMapFootballField();
	Skybox::CreateCubeMapFootballField2();

	Shapes::CreatePrism();
	Shapes::CreateCube();
	Shapes::CreateSphere(5);

	sf::Image img;
	if (!img.loadFromFile(UV_GRID_FILE))
		std::cout << "Error Loading Image";
	else
	{
		glGenTextures(1, &TextureId_UVGrind);
		glBindTexture(GL_TEXTURE_2D, TextureId_UVGrind);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	sf::Image img2;
	if (!img2.loadFromFile(UV_GRID_FILE2))
		std::cout << "Error Loading Image";
	else
	{
		glGenTextures(1, &TextureId_UVGrind2);
		glBindTexture(GL_TEXTURE_2D, TextureId_UVGrind2);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img2.getSize().x, img2.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img2.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glClearColor(0, 0.5, 0.5, 1);
	glEnable(GL_DEPTH_TEST);

	return 0;
}

float theta = 0.0f;
float theta_Light = 0.0f;
static void Update()
{
	// add all tick code
	theta += 0.005f;
	theta_Light += 0.05f;

	glUseProgram(programIDs[LIGHT]);
	GLuint Theta_Location_Light = glGetUniformLocation(programIDs[LIGHT], "theta");
	glUniform1f(Theta_Location_Light, theta_Light);

	glUseProgram(programIDs[BASIC]);
	GLuint Theta_Location = glGetUniformLocation(programIDs[BASIC], "theta");
	glUniform1f(Theta_Location, theta);
}

static void Render(float fov, glm::vec3 cameraPosition)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region Skybox
	// Skybox rendering
	glDepthMask(GL_FALSE);

	glUseProgram(programIDs[SKYBOX]);

	// Bind the first texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Skybox::DesertSkyboxTextureId);
	GLuint DesertSkyboxLocation = glGetUniformLocation(programIDs[SKYBOX], "DesertCubeMap");
	glUniform1i(DesertSkyboxLocation, 0);

	// Bind the second texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Skybox::FishPondSkyboxTextureId);
	GLuint FishPondSkyboxTextureLocation = glGetUniformLocation(programIDs[SKYBOX], "FishPondCubeMap");
	glUniform1i(FishPondSkyboxTextureLocation, 1);

	// Bind the third texture
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Skybox::FoooballFieldSkyboxTextureId);
	GLuint FoodballFieldSkyboxTextureLocation = glGetUniformLocation(programIDs[SKYBOX], "FoooballFieldCubeMap");
	glUniform1i(FoodballFieldSkyboxTextureLocation, 2);

	// Bind the third texture
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, Skybox::FoooballField2SkyboxTextureId);
	GLuint FoodballFieldSkyboxTextureLocation2 = glGetUniformLocation(programIDs[SKYBOX], "FoooballField2CubeMap");
	glUniform1i(FoodballFieldSkyboxTextureLocation2, 3);

	Shapes::BindCube();
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FoooballField2SkyboxTextureId);
	// Coordination
	glm::mat4 ModelMat_Skybox = glm::translate(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z)) *
		glm::scale(glm::vec3(50.f, 50.f, 50.f));
	glm::mat4 projMatSkybox = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Skybox program
	glUniformMatrix4fv(modelMatLocs[SKYBOX], 1, GL_FALSE, glm::value_ptr(ModelMat_Skybox));
	glUniformMatrix4fv(projMatLocs[SKYBOX], 1, GL_FALSE, glm::value_ptr(projMatSkybox));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	glDepthMask(GL_TRUE);
#pragma endregion Skybox

#pragma region Texture 1
	glUseProgram(programIDs[TEXTURES]);
	// Bind the first texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureId_UVGrind);
	GLuint textureLocation = glGetUniformLocation(programIDs[TEXTURES], "colormap");
	glUniform1i(textureLocation, 0);

	// Bind the second texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureId_UVGrind2);
	GLuint secondTextureLocation = glGetUniformLocation(programIDs[TEXTURES], "secondTexture");
	glUniform1i(secondTextureLocation, 1);

	//Textures rendering - Cube
	glUseProgram(programIDs[TEXTURES]);
	Shapes::BindCube();
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureId_UVGrind);
	// Coordination
	glm::mat4 ModelMat_Textures_Cube =
		glm::translate(glm::vec3(-6.f, 0.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatTexturesCube = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Textures program
	glUniformMatrix4fv(modelMatLocs[TEXTURES], 1, GL_FALSE, glm::value_ptr(ModelMat_Textures_Cube));
	glUniformMatrix4fv(projMatLocs[TEXTURES], 1, GL_FALSE, glm::value_ptr(projMatTexturesCube));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

	//Textures rendering - Sphere
	Shapes::BindSphere();
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureId_UVGrind2);
	// Coordination
	glm::mat4 ModelMat_Textures_Sphere =
		glm::translate(glm::vec3(0.f, 0.f, 0.f)) *
		glm::rotate(((theta * 2) * 1.5f) * 180 / 3.14f, glm::vec3(-1, -1, -1)) *
		glm::translate(glm::vec3(-3.0, 3.0, 0)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(1, 1, 1)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatTexturesSphere = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Textures program
	glUniformMatrix4fv(modelMatLocs[TEXTURES], 1, GL_FALSE, glm::value_ptr(ModelMat_Textures_Sphere));
	glUniformMatrix4fv(projMatLocs[TEXTURES], 1, GL_FALSE, glm::value_ptr(projMatTexturesSphere));
	glDrawArrays(GL_TRIANGLES, 0, Shapes::sphere_vertices.size());
#pragma endregion Texture 1

#pragma region Texture 2
	glUseProgram(programIDs[TEXTURES2]);
	Shapes::BindCube();
	// Coordination
	glm::mat4 ModelMat_Textures_Cube2 =
		glm::translate(glm::vec3(-6.f, 2.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatTexturesCube2 = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Textures program
	glUniformMatrix4fv(modelMatLocs[TEXTURES2], 1, GL_FALSE, glm::value_ptr(ModelMat_Textures_Cube2));
	glUniformMatrix4fv(projMatLocs[TEXTURES2], 1, GL_FALSE, glm::value_ptr(projMatTexturesCube2));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
#pragma endregion Texture 2

#pragma region Light
	// Sphere rendering
	glUseProgram(programIDs[LIGHT]);
	Shapes::BindSphere();
	// Coordination
	glm::mat4 ModelMat_Light =
		glm::translate(glm::vec3(0, 0, 0)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(1, 1, 1)) *
		glm::scale(glm::vec3(1, 1, 1));
	glm::mat4 projMatSphere = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Light program
	glUniformMatrix4fv(modelMatLocs[LIGHT], 1, GL_FALSE, glm::value_ptr(ModelMat_Light));
	glUniformMatrix4fv(projMatLocs[LIGHT], 1, GL_FALSE, glm::value_ptr(projMatSphere));
	glDrawArrays(GL_TRIANGLES, 0, Shapes::sphere_vertices.size());
#pragma endregion Light

#pragma region Reflection

	// Reflection rendering - Sphere
	glUseProgram(programIDs[REFLECTION]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::DesertSkyboxTextureId);
	GLuint reflectionTextureLocationDesert = glGetUniformLocation(programIDs[REFLECTION], "DesertCubeMap");
	glUniform1i(reflectionTextureLocationDesert, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FishPondSkyboxTextureId);
	GLuint reflectionTextureLocationFishPond = glGetUniformLocation(programIDs[REFLECTION], "FishPondCubeMap");
	glUniform1i(reflectionTextureLocationFishPond, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FoooballFieldSkyboxTextureId);
	GLuint reflectionTextureLocationFoooballField = glGetUniformLocation(programIDs[REFLECTION], "FoooballFieldCubeMap");
	glUniform1i(reflectionTextureLocationFoooballField, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FoooballField2SkyboxTextureId);
	GLuint reflectionTextureLocationFoooballField2 = glGetUniformLocation(programIDs[REFLECTION], "FoooballField2CubeMap");
	glUniform1i(reflectionTextureLocationFoooballField2, 3);

	Shapes::BindSphere();
	// Coordination
	glm::mat4 ModelMat_Reflection_Sphere =
		glm::translate(glm::vec3(0.f, 0.f, 0.f)) *
		glm::rotate((theta * 2) * 180 / 3.14f, glm::vec3(1, 1, 0)) *
		glm::translate(glm::vec3(3.f, -3.f, 0)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatReflectionSphere = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);

	// Set uniform matrices for the Reflection program
	glUniformMatrix4fv(modelMatLocs[REFLECTION], 1, GL_FALSE, glm::value_ptr(ModelMat_Reflection_Sphere));
	glUniformMatrix4fv(projMatLocs[REFLECTION], 1, GL_FALSE, glm::value_ptr(projMatReflectionSphere));

	glDrawArrays(GL_TRIANGLES, 0, Shapes::sphere_vertices.size());

	// Reflection rendering - Cube
	Shapes::BindCube();

	// Coordination
	glm::mat4 ModelMat_Reflection_Cube =
		glm::translate(glm::vec3(-6.f, -2.f, 0)) *
		glm::rotate((theta * 5) * 180 / 3.14f, glm::vec3(1, 1, 0)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatReflectionCube = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);

	// Set uniform matrices for the Reflection program
	glUniformMatrix4fv(modelMatLocs[REFLECTION], 1, GL_FALSE, glm::value_ptr(ModelMat_Reflection_Cube));
	glUniformMatrix4fv(projMatLocs[REFLECTION], 1, GL_FALSE, glm::value_ptr(projMatReflectionCube));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
#pragma endregion Reflection

#pragma region Refraction
	// Refraction rendering
	glUseProgram(programIDs[REFRACTION]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::DesertSkyboxTextureId);
	GLuint refractionTextureLocationDesert = glGetUniformLocation(programIDs[REFLECTION], "DesertCubeMap");
	glUniform1i(refractionTextureLocationDesert, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FishPondSkyboxTextureId);
	GLuint refractionTextureLocationFishPond = glGetUniformLocation(programIDs[REFLECTION], "FishPondCubeMap");
	glUniform1i(refractionTextureLocationFishPond, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FoooballFieldSkyboxTextureId);
	GLuint refractionTextureLocationFoooballField = glGetUniformLocation(programIDs[REFLECTION], "FoooballFieldCubeMap");
	glUniform1i(refractionTextureLocationFoooballField, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::FoooballField2SkyboxTextureId);
	GLuint refractionTextureLocationFoooballField2 = glGetUniformLocation(programIDs[REFLECTION], "FoooballField2CubeMap");
	glUniform1i(refractionTextureLocationFoooballField2, 3);

	Shapes::BindSphere();
	// Coordination
	glm::mat4 ModelMat_Refraction_Shpere =
		glm::translate(glm::vec3(0.f, 0.f, 0.f)) *
		glm::rotate((theta * 1.5f) * 180 / 3.14f, glm::vec3(-1, 1, -1)) *
		glm::translate(glm::vec3(3.f, 3.f, 0)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatRefraction_Shpere = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Refraction program
	glUniformMatrix4fv(modelMatLocs[REFRACTION], 1, GL_FALSE, glm::value_ptr(ModelMat_Refraction_Shpere));
	glUniformMatrix4fv(projMatLocs[REFRACTION], 1, GL_FALSE, glm::value_ptr(projMatRefraction_Shpere));
	glDrawArrays(GL_TRIANGLES, 0, Shapes::sphere_vertices.size());

	Shapes::BindCube();
	// Coordination
	glm::mat4 ModelMat_Refraction_Cube =
		glm::translate(glm::vec3(-6.f, -4.f, 0)) *
		glm::rotate((theta * 4) * 180 / 3.14f, glm::vec3(0, 1, 1)) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 projMatRefractionCube = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	// Set uniform matrices for the Refraction program
	glUniformMatrix4fv(modelMatLocs[REFRACTION], 1, GL_FALSE, glm::value_ptr(ModelMat_Refraction_Cube));
	glUniformMatrix4fv(projMatLocs[REFRACTION], 1, GL_FALSE, glm::value_ptr(projMatRefractionCube));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
#pragma endregion Refraction

	glUseProgram(programIDs[BASIC]);
	DrawHuman::draw(fov, theta, modelMatLocs[BASIC], projMatLocs[BASIC]);
}

int main()
{
	sf::ContextSettings context;
	context.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!", sf::Style::Close, context);
	window.setVerticalSyncEnabled(true);

	if (Init()) return 1;
	//window.setMouseCursorVisible(false);

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

	const float cameraSpeed = 5.0f;
	const float sensitivity = 0.5f;

	float yaws = -90.0f;
	float pitchs = 0.0f;

	bool firstMouse = true;
	float lastX = 0.0f, lastY = 0.0f;

	sf::Clock clock;

	std::cout << std::endl << std::endl
		<< "*****************************************************" << std::endl
		<< "Press 'Z' to change the skybox." << std::endl
		<< "Press 'T' to change the texures." << std::endl
		<< "Press 'C' to change the light." << std::endl
		<< "Press '1' to change the drawing mode to points." << std::endl
		<< "Press '2' to change the drawing mode to lines." << std::endl
		<< "Press '3' to change the drawing mode to filled triangles." << std::endl
		<< "Use the scroll to change the field of view." << std::endl
		<< "*****************************************************" << std::endl;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		ProcessInput::processInput(window, cameraPosition, cameraFront, cameraRight,
			cameraUp, cameraSpeed, sensitivity, yaws, pitchs, firstMouse, lastX, lastY, deltaTime);

		updateViewMatrix(cameraPosition, cameraFront, cameraUp);

		window.setMouseCursorVisible(false);
		//sf::Mouse::setPosition(sf::Vector2i(WIDTH / 2, HEIGHT / 2), window);

		Update();
		Render(ProcessInput::fov, cameraPosition);

		window.display();
	}
	return 0;
}