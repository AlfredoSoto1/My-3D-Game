#include "windowListener.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/component/Display.h"

using namespace listener;

WindowListener::WindowListener(void* displayPtr) {

	/*
		creates a lambda function with the corresponding action acording to its callback type
	*/

	auto positionCallback = [](GLFWwindow* window, int xpos, int ypos) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		displayPtr.setPosition(xpos, ypos);
		if (displayPtr.isDynamicallyUpdated())
			glfwSwapBuffers(window);
	};

	auto sizeCallback = [](GLFWwindow* window, int width, int height) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		displayPtr.setSize(width, height);
	};

	auto closeCallback = [](GLFWwindow* window) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.windowListener->closeCallbackAction != nullptr)
			displayPtr.windowListener->closeCallbackAction(glfwGetWindowUserPointer(window));
	};

	auto focusCallback = [](GLFWwindow* window, int isFocused) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.windowListener->onFocusCallbackAction != nullptr)
			displayPtr.windowListener->onFocusCallbackAction(glfwGetWindowUserPointer(window), isFocused);
	};

	auto iconifyCallback = [](GLFWwindow* window, int isIconified) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.windowListener->iconificationCallbackAction != nullptr)
			displayPtr.windowListener->iconificationCallbackAction(glfwGetWindowUserPointer(window), isIconified);
	};

	auto maximizeCallback = [](GLFWwindow* window, int isMaximized) {
	graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.windowListener->maximizedCallbackAction != nullptr)
			displayPtr.windowListener->maximizedCallbackAction(glfwGetWindowUserPointer(window), isMaximized);
	};

	auto refreshCallback = [](GLFWwindow* window) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.isDynamicallyUpdated())
			glfwSwapBuffers(window);
	};

	//convert via operator overload Display to GLFWwindpw pointer
	GLFWwindow* window = *(graphics::Display*)displayPtr;

	//sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(window, positionCallback);
	glfwSetWindowSizeCallback(window, sizeCallback);
	glfwSetWindowCloseCallback(window, closeCallback);
	glfwSetWindowFocusCallback(window, focusCallback);
	glfwSetWindowIconifyCallback(window, iconifyCallback);
	glfwSetWindowRefreshCallback(window, refreshCallback);
	glfwSetWindowMaximizeCallback(window, maximizeCallback);
}