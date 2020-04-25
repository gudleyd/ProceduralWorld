#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 u_Proj;
uniform mat4 u_View;

void main() {
	gl_Position = u_Proj * u_View * position;
}