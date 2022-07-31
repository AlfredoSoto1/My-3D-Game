#pragma once


#include <GL/glew.h>
#include "graphics/geometry/mesh.h"
#include "graphics/shader/shaderProgram.h"
#include "graphics/textures/bufferedTexture.h"

#include <stdlib.h>

class RendererTest {
public:

	texture::BufferedTexture* texture;

	geometry::Mesh* mesh;

	shader::Shader* rendererShader;
	shader::Uniform* u_Color;
	shader::TextureSampler* s_texture;

	shader::Shader* computeShader;
	shader::StorageBuffer* storageBuffer;
	shader::ImageBuffer* imageBuffer;

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

		u_Color = new shader::Uniform(*rendererShader, "u_Color");

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		float positions[8] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
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

		int width = 1280;
		int height = 720;
		char* pixels = new char[width * height * 4];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				pixels[(x + y * width) * 4 + 0] = rand() % 255;
				pixels[(x + y * width) * 4 + 1] = rand() % 255;
				pixels[(x + y * width) * 4 + 2] = rand() % 255;
				pixels[(x + y * width) * 4 + 3] = 255;
			}
		}

		texture = new texture::BufferedTexture(width, height, pixels);
		s_texture = new shader::TextureSampler(0, *rendererShader, "u_texture");

		delete[] pixels;

		//compute shader init

		const char* comp = "src/testCompute.shader";
		const char* shaderPath[1] = {comp};
		computeShader = new shader::Shader(1, shaderPath);

		imageBuffer = new shader::ImageBuffer(0, texture->getId(), texture->getInternalFormat());
		imageBuffer->bindImageBuffer();
		
		float data[4] = {1.0, 0.0, 1.0, 1.0};
		storageBuffer = new shader::StorageBuffer(0, sizeof(data), data);
	} 

	void render() {

		/*
			Compute Shader using shader storage buffer objects
		*/

		storageBuffer->bind();
		computeShader->dispatch(1280 / 16, 720 / 16, 1, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
		storageBuffer->unbind();

		/*
			traditional rendering strategy
		*/

		//shartShader Program
		rendererShader->onProgram();

		//load uniform value
		u_Color->setFloat4(1.0f, 0.0, 0.0, 1.0);

		//bind texture
		texture->bind(0);

		//bind mesh
		mesh->bind();

		//render/draw
		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		
		mesh->unbind();
		texture->unbind();
		rendererShader->offProgram();
	}

	void dispose() {
		delete texture;
		delete mesh;
		delete rendererShader;
		delete computeShader;
		delete u_Color;
		delete s_texture;
		delete storageBuffer;
		delete imageBuffer;
	}

private:

};

