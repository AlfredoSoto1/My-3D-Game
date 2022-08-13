#include "keyListener.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace listener;

KeyListener::KeyListener(void* displayPtr) {

	/*
		creates a lambda function with the corresponding action acording to its callback type
	*/

	auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		displayPtr.keyListener->keys[key] = action != GLFW_RELEASE;
	};

	auto charCallback = [](GLFWwindow* window, unsigned int codePoint) {

	};

	//allocates a block of memory which will contain all keys from keyboard.
	keys = new bool[GLFW_KEY_LAST];

	//convert via operator overload Display to GLFWwindpw pointer
	GLFWwindow* window = *(graphics::Display*)displayPtr;

	//sets the corresponding callback to GLFW
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCharCallback(window, charCallback);
}

KeyListener::~KeyListener() {
	delete keys;
}

bool KeyListener::isKeyDown(int key) {
	return (keys[key] == true) ? true : false;
}

bool KeyListener::isKeyToggled(int key) {
	if (isKeyDown(key)) {
		if (!toggled) {
			toggled = true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		toggled = false;
		return false;
	}
}

bool KeyListener::isKeyReleased(int key) {
	if (!isKeyDown(key)) {
		if (released) {
			released = false;
			return true;
		}
		return false;
	}
	else {
		released = true;
		return false;
	}
}

