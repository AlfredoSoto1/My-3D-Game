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
	shader::Uniform* u_viewMatrix;
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
		u_viewMatrix = new shader::Uniform(*rendererShader, "viewMatrix");

		unsigned int indices[12] = {
			0, 1, 2,
			2, 3, 0, 

			4, 5, 6,
			6, 7, 4
		};

		float positions[24] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f, 

			0.0f,  0.5f, -0.5f,
			0.0f, -0.5f, -0.5f,
			0.0f, -0.5f,  0.5f,
			0.0f,  0.5f,  0.5f

		};

		float textureCoords[16] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f, 

			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		mesh = new geometry::Mesh();
		mesh->createIndexBuffer(12, indices);
		mesh->createAttribute(0, 3, 8, positions, GL_FLOAT);
		mesh->createAttribute(1, 2, 8, textureCoords, GL_FLOAT);

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
		u_viewMatrix->setMatrix4f(camera->viewMatrix);

		//bind texture
		texture->bind(0);

		//bind mesh
		mesh->bind();

		//render/draw  
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		glDisable(GL_DEPTH_TEST);
		
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
		delete u_viewMatrix;
		delete s_texture;

		delete camera;
	}

private:

};

