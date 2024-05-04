#version 330

in vec4 frag_color;

//Colors
//uniform float theta;
//out vec4 FragColor;

void main()
{

	gl_FragColor = frag_color;

	//vec2 c = vec2(gl_FragCoord.x / 300.0 - 1.5, gl_FragCoord.y / 300.0 - 1.0);
	//float hue = mod(theta * 10.0, 1000.0) / 100.0;
	//FragColor = vec4(hue, 0, hue, 1.0);
}