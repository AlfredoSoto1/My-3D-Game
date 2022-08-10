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

		maths::structs::mat4 projectionMatrix;

		Camera();
		~Camera();

		void update();

	private:

	};

}

#endif // !_CAMERA_DEFINED

