#pragma once

#ifndef _CAMERA_DEFINED
#define _CAMERA_DEFINED

#include "../structs/maths.h"

namespace scene {

	class Camera {
	public:

		maths::structs::vec3 position;
		maths::structs::vec3 rotation;
		maths::structs::vec3 direction;

		maths::structs::mat4 viewMatrix;
		maths::structs::mat4 projectionMatrix;

		Camera();
		~Camera();

		void update();

	private:
		float fov = 45.0f; 
		float nearPlane = 0.1f;
		float farPlane = 1000.0f;

		float speed = 0.005f;

		void updateMovementDirection();
		float getDirectionSpeedFromKey(unsigned int key1, unsigned int key2, const float& speed);

	};

}

#endif // !_CAMERA_DEFINED

