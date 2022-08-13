#pragma once

#ifndef _CAMERA_DEFINED
#define _CAMERA_DEFINED

#include "../maths/vectors.h"
#include "../maths/matrix.h"

namespace scene {

	class Camera {
	public:

		maths::vec3 position;
		maths::vec3 rotation;
		maths::vec3 direction;

		maths::mat4 viewMatrix;
		maths::mat4 projectionMatrix;

		Camera();
		~Camera();

		void update();

	private:

		//camera lcok flag
		bool locked = true;
		bool lockedToggled = false;

		//mouse pixel difference across screen
		double xPixelDif = 0.0;
		double yPixelDif = 0.0;

		//camera adjustments
		float fov = 45.0f; 
		float nearPlane = 0.1f;
		float farPlane = 1000.0f;

		//sensitivity
		float xRotationSensitivity = 0.8f;
		float yRotationSensitivity = 0.8f;

		//motion
		float movementSpeed = 0.005f;

		bool checkIfCameraLocked();

		void updateViewMatrix();
		void updateProjectionMatrix();

		void calcCameraRotation(const double& milisecDif);
		void calcMovementDirection(const double& milisecDif);

		float getDirectionFromKey(unsigned int key1, unsigned int key2);

	};

}

#endif // !_CAMERA_DEFINED

