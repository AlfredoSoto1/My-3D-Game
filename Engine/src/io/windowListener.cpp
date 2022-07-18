#include "windowListener.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace listener;

WindowListener::WindowListener(void* displayPtr) {

	graphics::Display* displayPtr = (graphics::Display*)displayPtr;
	//GLFWwindow* window = displayPtr->getWindowId();

	auto positionCallback = [](GLFWwindow* window, int xpos, int ypos) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		//windowDisplay.setPosition(xpos, ypos);
		//if (windowDisplay.doUpdateDinamically())
		//	glfwSwapBuffers(window);
	};
}