

#include <iostream>

#include "graphics/component/Display.h"

//#include "RendererTest.h"
#include "paralax/Renderer.h"

int init();
int update();
int dispose();

//RendererTest* renderTest;

Renderer* renderer;

int main() {

	graphics::Display* window1 = new graphics::Display("Window 1", 1280, 720);
	
	window1->setTargetFps(graphics::Display::UNLIMITED_FPS);//graphics::Display::UNLIMITED_FPS
	window1->setDynamicUpdate(false);
	window1->setFuntions(&init, &update, &dispose);

	graphics::Display::build();

	delete window1;
	return 0;
}

//initiate GLFW/OpenGL context
int init() {

	glClearColor(0.0, 0.0, 0.0, 1.0);

	//renderTest = new RendererTest();
	//renderTest->init();

	renderer = new Renderer();
	renderer->init();

	return 0; //error code
}

//updates opengl scene
int update() {

	//always clear buffer before render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->render();
	//renderTest->render();

	return 0; //error code
}

//disposes or cleans everything created in memory by the library
int dispose() {
	delete renderer;
	//delete renderTest;
	return 0; //error code
}

//#include <Windows.h>
//
//std::string GetCurrentDirectory()
//{
//	char buffer[MAX_PATH];
//	GetModuleFileNameA(NULL, buffer, MAX_PATH);
//	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
//
//	return std::string(buffer).substr(0, pos);
//}
