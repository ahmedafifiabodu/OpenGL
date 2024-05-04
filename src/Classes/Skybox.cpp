#include "Skybox.h"

GLuint Skybox::DesertSkyboxTextureId, Skybox::FishPondSkyboxTextureId, Skybox::FoooballFieldSkyboxTextureId,
Skybox::FoooballField2SkyboxTextureId;

void Skybox::CreateCubeMapDesert()
{
	const std::string CUBEMAP_FILES[] = {
		"src\\Skybox\\Desert\\rt.png",
		"src\\Skybox\\Desert\\lf.png",
		"src\\Skybox\\Desert\\up.png",
		"src\\Skybox\\Desert\\dn.png",
		"src\\Skybox\\Desert\\bk.png",
		"src\\Skybox\\Desert\\ft.png"
	};

	glGenTextures(1, &DesertSkyboxTextureId);
	sf::Image img_Skybox;

	glBindTexture(GL_TEXTURE_CUBE_MAP, DesertSkyboxTextureId);
	for (GLuint i = 0; i < 6; i++)
	{
		img_Skybox.loadFromFile(CUBEMAP_FILES[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, img_Skybox.getSize().x, img_Skybox.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_Skybox.getPixelsPtr());
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::CreateCubeMapFishPond()
{
	const std::string CUBEMAP_FILES[] = {
		"src\\Skybox\\FishPond\\negx.jpg",
		"src\\Skybox\\FishPond\\posx.jpg",
		"src\\Skybox\\FishPond\\posy.jpg",
		"src\\Skybox\\FishPond\\negy.jpg",
		"src\\Skybox\\FishPond\\negz.jpg",
		"src\\Skybox\\FishPond\\posz.jpg"
	};

	glGenTextures(1, &FishPondSkyboxTextureId);
	sf::Image img_Skybox;

	glBindTexture(GL_TEXTURE_CUBE_MAP, FishPondSkyboxTextureId);
	for (GLuint i = 0; i < 6; i++)
	{
		img_Skybox.loadFromFile(CUBEMAP_FILES[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
			img_Skybox.getSize().x, img_Skybox.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_Skybox.getPixelsPtr());
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::CreateCubeMapFootballField()
{
	const std::string CUBEMAP_FILES[] = {
		"src\\Skybox\\Footballfield\\negx.jpg",
		"src\\Skybox\\Footballfield\\posx.jpg",
		"src\\Skybox\\Footballfield\\posy.jpg",
		"src\\Skybox\\Footballfield\\negy.jpg",
		"src\\Skybox\\Footballfield\\negz.jpg",
		"src\\Skybox\\Footballfield\\posz.jpg"
	};

	glGenTextures(1, &FoooballFieldSkyboxTextureId);
	sf::Image img_Skybox;

	glBindTexture(GL_TEXTURE_CUBE_MAP, FoooballFieldSkyboxTextureId);
	for (GLuint i = 0; i < 6; i++)
	{
		img_Skybox.loadFromFile(CUBEMAP_FILES[i]);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
			img_Skybox.getSize().x, img_Skybox.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_Skybox.getPixelsPtr());
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::CreateCubeMapFootballField2()
{
	const std::string CUBEMAP_FILES[] = {
		"src\\Skybox\\Footballfield2\\negx.jpg",
		"src\\Skybox\\Footballfield2\\posx.jpg",
		"src\\Skybox\\Footballfield2\\posy.jpg",
		"src\\Skybox\\Footballfield2\\negy.jpg",
		"src\\Skybox\\Footballfield2\\negz.jpg",
		"src\\Skybox\\Footballfield2\\posz.jpg"
	};

	glGenTextures(1, &FoooballField2SkyboxTextureId);
	sf::Image img_Skybox;

	glBindTexture(GL_TEXTURE_CUBE_MAP, FoooballField2SkyboxTextureId);
	for (GLuint i = 0; i < 6; i++)
	{
		img_Skybox.loadFromFile(CUBEMAP_FILES[i]);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
			img_Skybox.getSize().x, img_Skybox.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_Skybox.getPixelsPtr());
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}