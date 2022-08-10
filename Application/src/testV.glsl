//#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

out vec2 out_textureCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void) {
	
	out_textureCoords = textureCoords;

	vec4 positionRelativeToCamera = viewMatrix * vec4(position, -2.0, 1.0);

//	gl_Position = vec4(position, -2.0, 1.0);
	gl_Position = projectionMatrix * positionRelativeToCamera;
}