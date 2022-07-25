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
	unsigned int computeTexture;
	//unsigned int shaderStorageBuffer;

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

		texture = new texture::BufferedTexture(width, height, pixels);
		s_texture = new shader::TextureSampler(0, *rendererShader, "u_texture");

		delete[] pixels;

		//compute shader init

		const char* comp = "src/testCompute.shader";
		const char* computePath[1] = {comp};
		computeShader = new shader::Shader(1, computePath);

		//generate shader storage buffer id
		//glGenBuffers(1, &shaderStorageBuffer);

		int tex_w = 64, tex_h = 64;
		glGenTextures(1, &computeTexture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, computeTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			NULL);
		glBindImageTexture(0, computeTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
		//glBindImageTexture(0/*location*/, texture->getId(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

		//bind and store data
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);//bind
		//glBufferData(GL_SHADER_STORAGE_BUFFER, 0, (void*)0, GL_DYNAMIC_DRAW);
		//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0/*Bind location*/, shaderStorageBuffer);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);//unbind
	} 

	void render() {

		//update data inserted first time  --before shader start
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
		//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0/*offset*/, 0, (void*)0);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		computeShader->onProgram();

		glDispatchCompute(64, 64, 1);
		//glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		computeShader->offProgram();

		//read data from shader --after shader ends
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
		//glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0/*offset*/, 0, (void*)0);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);


		rendererShader->onProgram();
		//setting uniform variable values
		//u_Color->setFloat4(1.0f, 0.0, 0.0, 1.0);

		//texture->bind(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, computeTexture);

		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		mesh->unbind();

		rendererShader->offProgram();
	}

	void dispose() {
		delete texture;
		delete mesh;
		delete rendererShader;
		delete computeShader;
		delete u_Color;
		delete s_texture;

		//glDeleteBuffers(1, &shaderStorageBuffer);
	}

private:

};
