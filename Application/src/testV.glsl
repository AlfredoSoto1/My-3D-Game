//#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
//layout(location = 1) in vec2 textureCoords;

out vec2 out_textureCoords;
out vec3 out_normal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;

void main(void) {
	
	out_textureCoords = position.xz;
//	out_textureCoords = textureCoords;

	out_normal = normal;

	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;
}