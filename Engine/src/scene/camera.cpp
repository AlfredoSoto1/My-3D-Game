#include "camera.h"

#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace scene;
using namespace maths::structs;

graphics::Display* displayRef;

Camera::Camera() {
	GLFWwindow* window = glfwGetCurrentContext();
	displayRef = static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));

	//create projection matrix
	maths::structs::zero(&projectionMatrix);
	int width = 0;
	int height = 0;
	displayRef->getDimensions(&width, &height);
	calcProjectionMatrix(&projectionMatrix, farPlane, nearPlane, fov, width, height);


	//calc view matrix
	//public Matrix4f getViewMatrix() {
	//	viewMatrix.identity();
	//	viewMatrix.rotate((float)Math.toRadians(xRot), new Vector3f(1, 0, 0));
	//	viewMatrix.rotate((float)Math.toRadians(yRot), new Vector3f(0, 1, 0));
	//	Vector3f negativeCameraPos = new Vector3f(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	//	viewMatrix.translate(negativeCameraPos);
	//	return viewMatrix;
	//}
}

Camera::~Camera() {

}

void Camera::update() {

	//update projection matrix
	if (displayRef->resized()) {
		int width = 0;
		int height = 0;
		displayRef->getDimensions(&width, &height);

		calcProjectionMatrix(&projectionMatrix, farPlane, nearPlane, fov, width, height);
	}

	//move camera
	//FIXME
	float velx = 0.001f;
	float vely = 0.001f;
	float velz = 0.001f;

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_W)) {
		position.z -= velz;
	}

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_S)) {
		position.z += velz;
	}

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_A)) {
		position.x -= velx;
	}

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_D)) {
		position.x += velx;
	}

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_SPACE)) {
		position.y += vely;
	}

	if (displayRef->keyListener->isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		position.y -= vely;
	}

	//update view matrix
	maths::structs::identity(&viewMatrix);
	maths::structs::rotate(viewMatrix, &viewMatrix, rotation.y, maths::structs::vec3(0, 1, 0));
	maths::structs::rotate(viewMatrix, &viewMatrix, rotation.x, maths::structs::vec3(1, 0, 0));

	maths::structs::translate(viewMatrix, &viewMatrix, -position);
}


 