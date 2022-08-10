#pragma once

#include <GL/glew.h>
#include "graphics/geometry/mesh.h"
#include "graphics/shader/shaderProgram.h"
#include "graphics/textures/bufferedTexture.h"
#include "scene/camera.h"

#include "structs/maths.h"

#include <stdlib.h>

class RendererTest {
public:

	texture::BufferedTexture* texture;

	geometry::Mesh* mesh;

	shader::Shader* rendererShader;
	shader::Uniform* u_Color;
	shader::Uniform* u_projectionMatrix;
	shader::TextureSampler* s_texture;

	scene::Camera* camera;

	RendererTest() {

	}

	~RendererTest() {
		dispose();
	}

	void init() {

		const char* vert = "src/testV.glsl";
		const char* frag = "src/testF.glsl";

		const char* paths[2] = {vert, frag};

		rendererShader = new shader::Shader(2, paths);

		u_Color = new shader::Uniform(*rendererShader, "u_Color");
		u_projectionMatrix = new shader::Uniform(*rendererShader, "projectionMatrix");

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

		int width = 16;
		int height = 16;
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


		// camera
		camera = new scene::Camera();
	} 

	void render() {

		//update Camera
		camera->update();

		/*
			traditional rendering strategy
		*/

		//shartShader Program
		rendererShader->onProgram();

		//load uniform value
		u_Color->setFloat4(1.0f, 0.0, 0.0, 1.0);


		u_projectionMatrix->setMatrix4f(camera->projectionMatrix);

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
		delete u_Color;
		delete u_projectionMatrix;
		delete s_texture;

		delete camera;
	}

private:

};

