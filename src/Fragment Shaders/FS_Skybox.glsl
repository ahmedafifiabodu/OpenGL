#version 330

in vec3 color;
in vec3 frag_uv;

uniform samplerCube DesertCubeMap;
uniform samplerCube FishPondCubeMap;
uniform samplerCube FoooballFieldCubeMap;
uniform samplerCube FoooballField2CubeMap;
uniform int useSkybox = 0;

void main()
{             
    //gl_FragColor = texture(cubemap, frag_uv);

    if(useSkybox == 0) {
		gl_FragColor = texture(DesertCubeMap, frag_uv);
	} else if(useSkybox == 1) {
		gl_FragColor = texture(FishPondCubeMap, frag_uv);
	} else if(useSkybox == 2) {
		gl_FragColor = texture(FoooballFieldCubeMap, frag_uv);
	}  else if(useSkybox == 3) {
		gl_FragColor = texture(FoooballField2CubeMap, frag_uv);
	}
}