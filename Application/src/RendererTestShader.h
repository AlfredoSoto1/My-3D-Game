#pragma once

#include "graphics/shader/shaderProgram.h"

class RendererShader {
public:

	shader::Shader* rendererShader;

	RendererShader() {
		const char* vert = "src/testV.shader";
		const char* frag = "src/testF.shader";

		const char* paths[2] = { vert, frag };

		rendererShader = new shader::Shader(2, paths);

		//load uniforms

		//shader::Uniform<float> uVar("variableName");
		//uVar.set(10.0);

		shader::Uniform var("variableName", *rendererShader);
	}

	~RendererShader() {
		delete rendererShader;
	}

private:



};
