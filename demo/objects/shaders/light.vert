#version 330 core

layout (location = 0) in vec3 atribPos;

uniform mat4 worldMatrix;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * worldMatrix * vec4(atribPos, 1.0f);
}