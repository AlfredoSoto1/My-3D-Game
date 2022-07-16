#include "Display.h"

#define MIN_WIDTH 320
#define MIN_HEIGHT 180

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

using namespace graphics;

/*
	Basic Display constructor and destructor
*/

Display::Display() :
	title("Display"), width(MIN_WIDTH), height(MIN_HEIGHT) {

}

Display::Display(const char* title, int width, int height) :
title(title), width(width), height(height) {

}

Display::~Display() {

}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

/*
	Display built-in actions
*/

void Display::close() {
	if (window == nullptr)
		return;
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Display::focus() {
	if (window == nullptr)
		return;
	glfwFocusWindow(window);
}

void Display::restore() {
	isIconified = false;
	isMaximized = false;
	if (window == nullptr)
		return;
	glfwRestoreWindow(window);
}

void Display::minimize() {
	isIconified = true;
	isMaximized = false;
	if (window == nullptr)
		return;
	glfwIconifyWindow(window);
}

void Display::maximize() {
	isMaximized = true;
	isIconified = false;
	if (window == nullptr)
		return;
	glfwMaximizeWindow(window); 
}

void Display::requestAttention() {
	if (window == nullptr)
		return;
	glfwRequestWindowAttention(window);
}

void Display::centerCursorOnLaunch() {
	isCursorCentered = true;
}

/*
	set Display function propeties
*/

void Display::setTitle(const char* title) {
	this->title = title;
	if (window == nullptr)
		return;
	glfwSetWindowTitle(window, title);
}

void Display::setSize(int width, int height) {
	this->width = width;
	this->height = height;
	if (window == nullptr)
		return;
	glfwSetWindowSize(window, width, height);
}

void Display::setPosition(int x, int y) {
	this->xpos = x;
	this->ypos = y;
	if (window == nullptr)
		return;
	glfwSetWindowPos(window, x, y);
}

void Display::setVisible(bool isVisible) {
	this->isVisible = isVisible;
	if (window == nullptr)
		return;
	if (isVisible)
		glfwShowWindow(window);
	else
		glfwHideWindow(window);
}

void Display::setTransparent(float transparency) {
	this->transparency = transparency;
	if (window == nullptr)
		return;
	glfwSetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER, transparency > 0 ? GLFW_TRUE : GLFW_FALSE);
	glfwSetWindowOpacity(window, transparency);
}

void Display::setFuntions(int(*init)(), int(*update)(), int(*dispose)()) {
	this->init = init;
	this->update = update;
	this->dispose = dispose;
}

void Display::setFullscreen(bool isFullscreen) {
	this->isFullscreen = isFullscreen;
	if (window == nullptr)
		return;
	if (isFullscreen) {
		if (startUpMonitor == nullptr)
			setStartUpMonitor(currentMonitor);
		glfwGetWindowPos(window, &xpos, &ypos);
		glfwSetWindowMonitor(window, startUpMonitor, 0, 0, width, height, 0);
	}
	else {
		glfwSetWindowMonitor(window, 0, xpos, ypos, width, height, 0);
	}
	hasResized = true;
}

void Display::setTargetFps(int targetFrames) {
	if (targetFrames == VSYNC_FPS) {
		vsyncEnabled = true;
		this->targetFrames = VSYNC_FPS;
		if (window != nullptr)
			glfwSwapInterval(1);
	}
	else if (targetFrames == UNLIMITED_FPS) {
		vsyncEnabled = false;
		this->targetFrames = UNLIMITED_FPS;
		if (window != nullptr)
			glfwSwapInterval(0);
	}
	else {
		vsyncEnabled = false;
		if (targetFrames < 0)
			targetFrames = 60;
		this->targetFrames = targetFrames;
		if (window != nullptr)
			glfwSwapInterval(0);
	}
}

void Display::setStartUpMonitor(int monitor) {
	if (monitor < 0)
		monitor = 0;
	currentMonitor = monitor;
	if (window == nullptr)
		return;
	int monitorCount = 0;
	GLFWmonitor** availableMonitors = glfwGetMonitors(&monitorCount);
	startUpMonitor = availableMonitors[monitor %= monitorCount];
}

/*
	Display attributes
*/

void Display::setAlwaysOnTop(bool isAlwaysOnTop) {
	this->isAlwaysOnTop = isAlwaysOnTop;
	if (window == nullptr)
		return;
	glfwSetWindowAttrib(window, GLFW_FLOATING, isAlwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
}

void Display::setResizable(bool isResizable) {
	this->isResizable = isResizable;
	if (window == nullptr)
		return;
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, isResizable ? GLFW_TRUE : GLFW_FALSE);
}

void Display::setDecorated(bool isDecorated) {
	this->isDecorated = isDecorated;
	if (window == nullptr)
		return;
	glfwSetWindowAttrib(window, GLFW_DECORATED, isDecorated ? GLFW_TRUE : GLFW_FALSE);
}

void Display::build() {
	createDisplay();
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

		processFrames();
	}

	dispose();
	glfwDestroyWindow(window);
	isRunning = false;

	glfwTerminate();
}

/*
	Private functions
*/

void Display::processFrames() {
	//Current thread sleeps here to get targeted FPS
	if (!vsyncEnabled && targetFrames != UNLIMITED_FPS) {
		while (glfwGetTime() < lastTime + 1.0 / targetFrames);
		lastTime += 1.0 / targetFrames;
	}
	//Calculates FPS
	frames++;
	if (glfwGetTime() * 1000.0 > lastRefresh + 1000.0) {
		std::cout << "FPS: " << frames << std::endl;
		frames = 0;
		lastRefresh = glfwGetTime() * 1000.0;
	}
}

void Display::createDisplay() {
	//setting error callback
	glfwSetErrorCallback(&error_callback);

	if (!glfwInit()) {
		std::cout << "GLFW couldn't initiated correctly" << std::endl;
		return;
	}

	if (!createWindow())
		return;
	setWindowAttribs();
	centerWindow();

	//create Display context
	glfwMakeContextCurrent(window);

	setTargetFps(this->targetFrames);
	glfwShowWindow(window);

	if (!initGLEW())
		return;
	isRunning = true;
	glViewport(0, 0, width, height);
}

bool Display::createWindow() {
	setWindowHints();
	window = glfwCreateWindow(width, height, title, isFullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	return true;
}

void Display::setWindowHints() {
	glfwDefaultWindowHints();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, isVisible ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, isDecorated ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_FLOATING, isAlwaysOnTop ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, isMaximized && !isIconified ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, isResizable ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, isCursorCentered  ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparency > 0.0f ? GL_TRUE : GL_FALSE);
}

void Display::centerWindow() {
	if (startUpMonitor == nullptr)
		setStartUpMonitor(currentMonitor);
	const GLFWvidmode* videoMode = glfwGetVideoMode(startUpMonitor);
	if (isMaximized)
		return;
	this->xpos = (videoMode->width - this->width) / 2;
	this->ypos = (videoMode->height - this->height) / 2;
	glfwSetWindowPos(window, xpos, ypos);
}

void Display::setWindowAttribs() {
	if (isResizable)
		glfwSetWindowSizeLimits(window, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
	if (isIconified)
		minimize();
	if (transparency > 0)
		setTransparent(transparency);
}

bool Display::initGLEW() {
	if (glewInit() != GLEW_OK) {
		std::cout << "Couldn't inititate GLEW correctly" << std::endl;
		return false;
	}
	else {
		std::cout << glGetString(GL_VERSION) << std::endl;
		return true;
	}
}
