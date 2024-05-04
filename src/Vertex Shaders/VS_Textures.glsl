#version 330

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_uv;
layout (location = 3) in vec2 vertex_uv2;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 color;
out vec2 frag_uv;
out vec2 frag_uv2; 

void main()
{
	gl_Position = projMat * viewMat * modelMat * vertex_position;
	color = vertex_normal;
	frag_uv = vertex_uv;
	frag_uv2 = vertex_uv2;
}