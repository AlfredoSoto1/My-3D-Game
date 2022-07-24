#pragma once


#include <GL/glew.h>
#include "graphics/geometry/mesh.h"
#include "graphics/shader/shaderProgram.h"
#include "graphics/textures/bufferedTexture.h"

#include <stdlib.h>

class RendererTest {
public:

	int textureUniform;
	texture::BufferedTexture* texture;

	geometry::Mesh* mesh;

	shader::Shader* rendererShader;
	shader::Uniform* u_Color;

	RendererTest() {

	}

	~RendererTest() {
		dispose();
	}

	void init() {

		const char* vert = "src/testV.shader";
		const char* frag = "src/testF.shader";

		const char* paths[2] = {vert, frag};

		rendererShader = new shader::Shader(2, paths);

		u_Color = new shader::Uniform("u_Color", *rendererShader);

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		float positions[8] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		float textureCoords[8] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		mesh = new geometry::Mesh();
		mesh->createIndexBuffer(6, indices);
		mesh->createAttribute(0, 2, 4, positions, GL_FLOAT);
		mesh->createAttribute(1, 2, 4, textureCoords, GL_FLOAT);

		int width = 64;
		int height = 64;
		char* pixels = new char[width * height * 4];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				pixels[(x + y * width) * 4 + 0] = rand() % 255;
				pixels[(x + y * width) * 4 + 1] = rand() % 255;
				pixels[(x + y * width) * 4 + 2] = rand() % 255;
				pixels[(x + y * width) * 4 + 3] = 255;
			}
		}

		textureUniform = glGetUniformLocation(*rendererShader, "u_texture");
		texture = new texture::BufferedTexture(width, height, pixels);

		delete[] pixels;
	} 

	void render() {

		rendererShader->onProgram();

		//setting uniform variable values
		u_Color->setFloat4(1.0f, 0.0, 0.0, 1.0);


		texture->bind(0);
		glUniform1i(textureUniform, 0);


		mesh->bind();
		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		mesh->unbind();

		rendererShader->offProgram();
	}

	void dispose() {
		delete texture;
		delete mesh;
		delete rendererShader;
		delete u_Color;
	}

private:

};
