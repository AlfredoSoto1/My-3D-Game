#include "mouseListener.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../graphics/component/Display.h"

using namespace listener;

MouseListener::MouseListener(void* displayPtr)
	: displayPtr(displayPtr)
{

	/*
		creates a lambda function with the corresponding action acording to its callback type
	*/

	auto dropCallback = [](GLFWwindow* _window, int _pathCount, const char** _paths) {
		//FIXME
		//display::Window& windowDisplay = *static_cast<display::Window*>(glfwGetWindowUserPointer(_window));
		//windowDisplay.mouseListener->pathCount = _pathCount;
		//windowDisplay.mouseListener->droppedPaths = _paths;
	};

	auto enterCallback = [](GLFWwindow* window, int isInside) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		if (displayPtr.mouseListener->mouseEnterCallbackAction != nullptr)
			displayPtr.mouseListener->mouseEnterCallbackAction(glfwGetWindowUserPointer(window), isInside);
	};

	auto clickCallback = [](GLFWwindow* window, int button, int action, int mods) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		displayPtr.mouseListener->buttons[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* window, double xOffset, double yOffset) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		displayPtr.mouseListener->xScroll = xOffset;
		displayPtr.mouseListener->yScroll = yOffset;
	};

	auto positionCallback = [](GLFWwindow* window, double xpos, double ypos) {
		graphics::Display& displayPtr = *static_cast<graphics::Display*>(glfwGetWindowUserPointer(window));
		//store mouse position
		displayPtr.mouseListener->xPosition = xpos;
		displayPtr.mouseListener->yPosition = ypos;

		//store mouse normalized position
		int width, height;
		displayPtr.getDimensions(&width, &height);
		displayPtr.mouseListener->xNormalized = (xpos * 2.0) / width - 1.0;
		displayPtr.mouseListener->yNormalized = -(ypos * 2.0) / height + 1.0;
	};

	//allocates a block of memory which will contain all buttons from mouse.
	buttons = new bool[GLFW_MOUSE_BUTTON_LAST];

	//convert via operator overload Display to GLFWwindpw pointer
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	
	//sets the corresponding callback to GLFW
	glfwSetDropCallback(window, dropCallback);
	glfwSetCursorEnterCallback(window, enterCallback);
	glfwSetMouseButtonCallback(window, clickCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, positionCallback);
}

MouseListener::~MouseListener() {
	delete[] buttons;
}

bool MouseListener::isButtonDown(int button) {
	return buttons[button];
}

void MouseListener::getMouseSpeed(double* xSpeed, double* ySpeed) {
	*xSpeed = xPosition - lastXPosition;
	lastXPosition = xPosition;
	*ySpeed = yPosition - lastYPosition;
	lastYPosition = yPosition;
}

void MouseListener::getMousePosition(double* xpos, double* ypos) {
	*xpos = xPosition;
	*ypos = yPosition;
}

void MouseListener::speedToZero() {
	lastXPosition = xPosition;
	lastYPosition = yPosition;
}

//void* MouseListener::setCursorShape(unsigned int cursorShape) {
//	switch (cursorShape) {
//	case IBEAM:
//		return glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
//	case HAND:
//		return glfwCreateStandardCursor(GLFW_HAND_CURSOR);
//	case CROSSHAIR:
//		return glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
//	case HRESIZE:
//		return glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
//	case VRESIZE:
//		return glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
//	default:
//		return glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
//	}
//}

void MouseListener::setCursor(void* cursor) {
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	GLFWcursor* cursorRef = (GLFWcursor*)cursor;
	glfwSetCursor(window, cursorRef);
}

void MouseListener::destroy(void* cursor) {
	GLFWcursor* cursorRef = (GLFWcursor*)cursor;
	glfwDestroyCursor(cursorRef);
}

void MouseListener::hideCursor() {
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void MouseListener::grabCursor() {
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MouseListener::defaultCursor() {
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MouseListener::setCursorPosition(double x, double y) {
	GLFWwindow* window = *(graphics::Display*)displayPtr;
	glfwSetCursorPos(window, x, y);
	xPosition = x;
	yPosition = y;
	lastXPosition = x;
	lastYPosition = y;
}