#include "Display.h"

#define MIN_WIDTH 320
#define MIN_HEIGHT 180

#include <iostream>

using namespace graphics;

Display::Display() {

}

Display::Display(const char* title, int width, int height) :
title(title), width(width), height(height) {

}

Display::~Display() {

}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void Display::close() {

}

void Display::restore() {

}

void Display::minimize() {

}

void Display::maximize() {

}

void Display::requestAttention() {

}

void Display::centerCursorOnLaunch() {

}

void Display::setTitle(const char* title) {

}

void Display::setSize(int width, int height) {

}

void Display::setPosition(int x, int y) {

}

void Display::setAlwaysOnTop(bool isAlwaysOnTop) {

}

void Display::setResizable(bool isResizable) {

}

void Display::setDecorated(bool isDecorated) {

}

void Display::setVisible(bool isVisible) {

}

void Display::setFullscreen(bool isFullscreen) {

}

void Display::setTransparent(float transparency) {

}

void Display::build(int(*init)(), int(*update)(), int(*dispose)()) {
	
	createContextDisplay();
	//create input here
	init();

	while (!glfwWindowShouldClose(window)) {
		if (hasResized)
			glViewport(0, 0, width, height);
		
		update();

		//update display
		glfwSwapBuffers(window);
		hasResized = false;
		glfwPollEvents();

		displayFrames();
	}

	dispose();
	glfwDestroyWindow(window);

	stillActive = false;

	glfwTerminate();
	
}

void Display::displayFrames() {
	frames++;
	if (glfwGetTime() * 1000.0 > time + 1000.0) {
		std::cout << "FPS: " << frames << std::endl;
		frames = 0;
		time = glfwGetTime() * 1000.0;
	}
}

void Display::createContextDisplay() {
	//setting error callback
	glfwSetErrorCallback(&error_callback);

	if (!glfwInit()) {
		std::cout << "GLFW couldn't initiated correctly" << std::endl;
		return;
	}

	//preprocess instructions
	preprocessPrepare();

	//create window
	window = glfwCreateWindow(width, height, title, isFullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	//process instructions
	processPrepare();

	centerWindow();

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	glfwShowWindow(window);

	glViewport(0, 0, width, height);


	if (glewInit() != GLEW_OK)
		std::cout << "Couldn't inititate GLEW correctly" << std::endl;
	else
		std::cout << glGetString(GL_VERSION) << std::endl;

	this->stillActive = true;
}

void Display::preprocessPrepare() {
	glfwDefaultWindowHints();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, isVisible ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, isDecorated ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_FLOATING, isAlwaysOnTop ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, isIconified && !isMaximized ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, isMaximized && !isIconified ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, isResizable ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, isCursorCentered  ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparency > 0.0f ? GL_TRUE : GL_FALSE);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

}

void Display::centerWindow() {
	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	this->xpos = (videoMode->width - this->width) / 2;
	this->ypos = (videoMode->height - this->height) / 2;
	glfwSetWindowPos(window, xpos, ypos);
}

void Display::processPrepare() {
	if (isResizable) {
		glfwSetWindowSizeLimits(window, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
}

