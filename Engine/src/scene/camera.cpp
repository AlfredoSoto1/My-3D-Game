#include "camera.h"

#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace scene;
using namespace maths::structs;

graphics::Display display;

Camera::Camera() {
	GLFWwindow* window = glfwGetCurrentContext();
	display = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));

	maths::structs::zero(&projectionMatrix);
}

Camera::~Camera() {

}

void Camera::update() {
	if (display.resized()) {
		int width = 0;
		int height = 0;
		display.getDimensions(&width, &height);

		calcProjectionMatrix(&projectionMatrix, 1000.0, 0.1, 45.0, width, height);
	}
}
 