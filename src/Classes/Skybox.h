#pragma once
#include "../Main.h"

class Skybox
{
public:
	static GLuint DesertSkyboxTextureId, FishPondSkyboxTextureId,
		FoooballFieldSkyboxTextureId, FoooballField2SkyboxTextureId;

	static void CreateCubeMapDesert();
	static void CreateCubeMapFishPond();
	static void CreateCubeMapFootballField();
	static void CreateCubeMapFootballField2();
};
