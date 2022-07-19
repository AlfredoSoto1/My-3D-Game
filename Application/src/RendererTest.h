#pragma once


#include <GL/glew.h>
#include "graphics/geometry/mesh.h"
#include "graphics/shader/shaderProgram.h"

class RendererTest : shader::ShaderProgram {
public:

	geometry::Mesh* mesh;

	int uniformId;

	RendererTest() {

	}
	~RendererTest() {
		dispose();
	}

	void init() {


		createShader("src/testV.shader", "src/testF.shader", nullptr, nullptr);

		uniformId = glGetUniformLocation(program, "u_Color");

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

		mesh = new geometry::Mesh();
		mesh->createIndexBuffer(6, indices);
		mesh->createAttribute(0, 2, 4, positions, GL_FLOAT);
	}

	void render() {

		glUseProgram(program);

		glUniform4f(uniformId, 1.0, 0.0, 0.0, 1.0);

		mesh->bind();

		glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);

		mesh->unbind();

		glUseProgram(0);
	}

	void dispose() {
		delete mesh;
	}

private:

};
