#version 330

in vec3 frag_position;
in vec3 frag_normal;

uniform samplerCube DesertCubeMap;
uniform samplerCube FishPondCubeMap;
uniform samplerCube FoooballFieldCubeMap;
uniform samplerCube FoooballField2CubeMap;
uniform int useSkybox = 0;

uniform vec3 camera_position;

void main()
{             
	vec3 r = reflect( normalize (frag_position - camera_position), normalize(frag_normal));

	if(useSkybox == 0) {
		gl_FragColor = texture(DesertCubeMap, r);
	} else if(useSkybox == 1) {
		gl_FragColor = texture(FishPondCubeMap, r);
	} else if(useSkybox == 2) {
		gl_FragColor = texture(FoooballFieldCubeMap, r);
	} else if(useSkybox == 3) {
		gl_FragColor = texture(FoooballField2CubeMap, r);
	}

}