#include "camera.h"

#include "../maths/functions.h"
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace scene;

graphics::Display* displayRef;

Camera::Camera() {
	GLFWwindow* window = glfwGetCurrentContext();
	displayRef = static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));

	//create projection matrix
	maths::zero(&projectionMatrix);
	updateProjectionMatrix();
}

Camera::~Camera() {

}

void Camera::update() {
	//toggle to be camera on lock (TEMP)
	if (displayRef->keyListener->isKeyToggled(GLFW_KEY_P))
		if (locked)
			locked = false;
		else
			locked = true;

	double milisecDif = displayRef->timeDifference * 1000.0;//miliseconds

	//update projection matrix
	if (displayRef->resized() ) {
		updateProjectionMatrix();
	}

	//move camera
	displayRef->mouseListener->getMouseSpeed(&xPixelDif, &yPixelDif);
	
	if (checkIfCameraLocked())
		return;

	calcCameraRotation(milisecDif);
	calcMovementDirection(milisecDif);

	//update camera position
	position += direction;

	//update view matrix
	updateViewMatrix();
}

bool Camera::checkIfCameraLocked() {
	if (locked) {
		if (!lockedToggled) {
			lockedToggled = true;
			int width = 0;
			int height = 0;
			displayRef->getDimensions(&width, &height);
			//set cursor to default propeties and default position (center of window)
			displayRef->mouseListener->defaultCursor();
			displayRef->mouseListener->setCursorPosition(width / 2.0, height / 2.0);
			//reset pixelDif to zero
			xPixelDif = 0.0;
			yPixelDif = 0.0;
		}
		return true;
	}
	else {
		if (lockedToggled) {
			lockedToggled = false;
			displayRef->mouseListener->grabCursor();
		}
		return false;
	}
}

void Camera::updateProjectionMatrix() {
	int width = 0;
	int height = 0;
	displayRef->getDimensions(&width, &height);
	//calculates the projection matrix at current viewport
	project(&projectionMatrix, farPlane, nearPlane, fov, width, height);
}

void Camera::updateViewMatrix() {
	maths::identity(&viewMatrix);
	//rotates matrix in the x-axis
	maths::rotate(viewMatrix, &viewMatrix, maths::toRadians(rotation.x), maths::vec3(1, 0, 0));
	//rotates matrix in the y-axis
	maths::rotate(viewMatrix, &viewMatrix, maths::toRadians(rotation.y), maths::vec3(0, 1, 0));
	//translate matrix relative to camera position
	maths::translate(viewMatrix, &viewMatrix, -position);
}

void Camera::calcCameraRotation(const double& milisecDif) {
	rotation += maths::vec3(yPixelDif * milisecDif * yRotationSensitivity, xPixelDif * milisecDif * xRotationSensitivity, 0.0/*z-axis rot*/);
	
	rotation.x = rotation.x >  90.0f ?  90.0f : rotation.x;
	rotation.x = rotation.x < -90.0f ? -90.0f : rotation.x;
}

void Camera::calcMovementDirection(const double& milisecDif) {
	//gets corresponding direction according to pressed keys (W,A,S,D, SPACE, L_SHIFT)
	float xDir = getDirectionFromKey(GLFW_KEY_D, GLFW_KEY_A);
	float yDir = getDirectionFromKey(GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);
	float zDir = getDirectionFromKey(GLFW_KEY_S, GLFW_KEY_W);
	direction.set(xDir, yDir, zDir);
	maths::normalize(&direction);

	//update camera view direction
	float yRotationRadians = maths::toRadians(rotation.y);
	float xViewDir = sin(yRotationRadians);
	float zViewDir = cos(yRotationRadians);

	//combines camera direction with movement direction
	float xDisplacement = zViewDir * direction.x - xViewDir * direction.z;
	float zDisplacement = zViewDir * direction.z + xViewDir * direction.x;
	direction.set(xDisplacement, direction.y, zDisplacement);

	//apply speed to camera when moving
	direction *= milisecDif * movementSpeed;
}

float Camera::getDirectionFromKey(unsigned int key1, unsigned int key2) {
	if (displayRef->keyListener->isKeyDown(key1) && displayRef->keyListener->isKeyDown(key2))
		return 0.0f;
	else if (displayRef->keyListener->isKeyDown(key1))
		return 1.0f;
	else if (displayRef->keyListener->isKeyDown(key2))
		return -1.0f;
	return 0.0f;
}
 