#pragma once

#include <GL/glew.h>
#include "graphics/geometry/mesh.h"
#include "graphics/shader/shaderProgram.h"
#include "graphics/textures/bufferedTexture.h"
#include "scene/camera.h"

#include "maths/matrix.h"

#include "chunkBuilder.h"

class RendererTest {
public:

	texture::BufferedTexture* texture;

	geometry::Mesh* mesh;

	shader::Shader* rendererShader;
	shader::Uniform* u_Color;
	shader::Uniform* u_projectionMatrix;
	shader::Uniform* u_transformationMatrix;
	shader::Uniform* u_viewMatrix;
	shader::TextureSampler* s_texture;

	maths::mat4 transformationMatrix;

	scene::Camera* camera;

	generation::ChunkBuilder* chunkBuilder;
	 
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
		u_transformationMatrix = new shader::Uniform(*rendererShader, "transformationMatrix");

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

		//float textureCoords[16] = {
		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f, 

		//	0.0f, 0.0f,
		//	1.0f, 0.0f,
		//	1.0f, 1.0f,
		//	0.0f, 1.0f
		//};

		chunkBuilder = new generation::ChunkBuilder();
		chunkBuilder->buildExample();

		mesh = new geometry::Mesh();

		//unsigned int triangles = chunkBuilder->modelCoordListLength / 3;
		//unsigned int lessVertices = (triangles - 20) * 3;

		mesh->createIndexBuffer(chunkBuilder->modelIndexListLength, chunkBuilder->modelIndices);
		mesh->createAttribute(0, 3, chunkBuilder->modelCoordListLength, chunkBuilder->modelCoords, GL_FLOAT);
		mesh->createAttribute(1, 3, chunkBuilder->modelCoordListLength, chunkBuilder->modelNormals, GL_FLOAT);

		//mesh->createIndexBuffer(12, indices);
		//mesh->createAttribute(0, 3, 8, positions, GL_FLOAT);
		//mesh->createAttribute(1, 2, 8, textureCoords, GL_FLOAT);

		int width = 16;
		int height = 16;
		char* pixels = new char[width * height * 4];
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				pixels[(x + y * width) * 4 + 0] = 24  * (24.0  / (rand() % 24 ));//Red
				pixels[(x + y * width) * 4 + 1] = 147 * (147.0 / (rand() % 147));//Green
				pixels[(x + y * width) * 4 + 2] = 66  * (66.0  / (rand() % 66 ));//Blue
				pixels[(x + y * width) * 4 + 3] = 255;//alpha
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

		//apply view and projection matrix
		u_projectionMatrix->setMatrix4f(camera->projectionMatrix);
		u_viewMatrix->setMatrix4f(camera->viewMatrix);

		//apply transformation matrix
		maths::transform(&transformationMatrix, maths::vec3(0.0), maths::vec3(0.0), maths::vec3(1.0));
		u_transformationMatrix->setMatrix4f(transformationMatrix);

		//bind texture
		texture->bind(0);

		//bind mesh
		mesh->bind();

		//render/draw  
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		glDisable(GL_CULL_FACE);
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
		delete u_transformationMatrix;
		delete u_viewMatrix;
		delete s_texture;

		delete camera;


		delete chunkBuilder;
	}

private:

};

