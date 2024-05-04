#version 330

in vec3 color;
in vec2 frag_uv;
in vec2 frag_uv2;

out vec4 FragColor;

uniform sampler2D colormap;
uniform sampler2D secondTexture;

uniform int usetexture = 0;

void main()
{
	if(usetexture == 0) {
		FragColor = texture(colormap, frag_uv);
	} else if(usetexture == 1) {
		FragColor = texture(secondTexture, frag_uv);
	} else if(usetexture == 2) {
		FragColor = vec4(color, 1.0);
	}
}