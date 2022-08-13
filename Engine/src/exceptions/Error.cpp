#include "Error.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void error::glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void error::glCheckError() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: " << error << std::endl;
	}
}

void error::throwOutBoundsError(unsigned int offNumber, unsigned int limit) {
	std::cout << "Index out of bounds! " << offNumber << " of " << limit << std::endl;
}