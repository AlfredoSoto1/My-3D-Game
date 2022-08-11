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
	double gameTick = displayRef->currentGameTick * 1000.0;

	double xSpeed = 0.001;
	double ySpeed = 0.001;
	//displayRef->mouseListener->getMouseSpeed(&xSpeed, &ySpeed);

	xSpeed = getDirectionSpeedFromKey(GLFW_KEY_RIGHT, GLFW_KEY_LEFT, xSpeed);
	ySpeed = getDirectionSpeedFromKey(GLFW_KEY_DOWN, GLFW_KEY_UP, ySpeed);

	updateMovementDirection();

	//update camera view direction
	rotation += maths::structs::vec3(ySpeed * gameTick * 360.0f, xSpeed * gameTick * 360.0f, 0.0);

	float yRotationRadians = maths::functions::toRadians(rotation.y);
	float sinRot = sin(yRotationRadians);
	float cosRot = cos(yRotationRadians);

	float xDisplacement = cosRot * direction.x - sinRot * direction.z;
	float zDisplacement = cosRot * direction.z + sinRot * direction.x;

	direction.set(xDisplacement, direction.y, zDisplacement);
	direction *= gameTick;

	position += direction;

	//update view matrix
	maths::structs::identity(&viewMatrix);
	maths::structs::rotate(viewMatrix, &viewMatrix, maths::functions::toRadians(rotation.x), maths::structs::vec3(1, 0, 0));
	maths::structs::rotate(viewMatrix, &viewMatrix, maths::functions::toRadians(rotation.y), maths::structs::vec3(0, 1, 0));

	maths::structs::translate(viewMatrix, &viewMatrix, -position);
}

void Camera::updateMovementDirection() {
	float xDir = getDirectionSpeedFromKey(GLFW_KEY_D, GLFW_KEY_A, speed);
	float yDir = getDirectionSpeedFromKey(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT, speed);
	float zDir = getDirectionSpeedFromKey(GLFW_KEY_S, GLFW_KEY_W, speed);

	direction.set(xDir, yDir, zDir);
}

float Camera::getDirectionSpeedFromKey(unsigned int key1, unsigned int key2, const float& speed) {
	if (displayRef->keyListener->isKeyDown(key1) && displayRef->keyListener->isKeyDown(key2))
		return 0.0f;
	else if (displayRef->keyListener->isKeyDown(key1))
		return speed;
	else if (displayRef->keyListener->isKeyDown(key2))
		return -speed;
	return 0.0f;
}


 