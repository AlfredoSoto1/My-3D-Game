
#include "graphics/component/Display.h"

#include "RendererTest.h"

int init();
int update();
int dispose();

RendererTest* renderTest;

int main() {

	graphics::Display* window1 = new graphics::Display("Window 1", 1280, 720);

	window1->setDynamicUpdate(false);
	window1->setFuntions(&init, &update, &dispose);

	graphics::Display::build();

	delete window1;
	return 0;
}

//initiate GLFW/OpenGL context
int init() {

	glClearColor(0.0, 0.0, 0.0, 1.0);

	renderTest = new RendererTest();
	renderTest->init();
	return 0; //error code
}

//updates opengl scene
int update() {

	//always clear buffer before render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderTest->render();
	return 0; //error code
}

//disposes or cleans everything created in memory by the library
int dispose() {
	delete renderTest;
	return 0; //error code
}





//#define GLEW_STATIC
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <thread>
//
//GLFWwindow* window;
//GLFWwindow* display;
//
//int runningThreads = 2;
//
//void run1() {
//    glfwMakeContextCurrent(window);
//    while (!glfwWindowShouldClose(window)) {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glBegin(GL_TRIANGLES);
//
//        glVertex2f(-.5, 0.0);
//        glVertex2f(.5, 0.0);
//        glVertex2f(0.0, -.5);
//
//        glEnd();
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    runningThreads--;
//}
//
//void run2() {
//    glfwMakeContextCurrent(display);
//    while (!glfwWindowShouldClose(display)) {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glBegin(GL_TRIANGLES);
//
//        glVertex2f(-.5, 0.0);
//        glVertex2f(.5, 0.0);
//        glVertex2f(0.0, -.5);
//
//        glEnd();
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(display);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    runningThreads--;
//}
//
//int main(void) {
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World 1", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    display = glfwCreateWindow(640, 480, "Hello World 2", NULL, NULL);
//    if (!display)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    //glfwMakeContextCurrent(window);
//
//    //if (glewInit() != GLEW_OK)
//        //std::cout << "Could not initiate glew!" << std::endl;
//
//    //std::cout << glGetString(GL_VERSION) << std::endl;
//
//    //glfwMakeContextCurrent(display);
//
//    //if (glewInit() != GLEW_OK)
//    //    std::cout << "Could not initiate glew!" << std::endl;
//
//    //std::cout << glGetString(GL_VERSION) << std::endl;
//
//    std::thread* thread1 = new std::thread(&run1);
//    thread1->detach();
//    std::thread* thread2 = new std::thread(&run2);
//    thread2->detach();
//
//    while (runningThreads > 0)
//    {
//        //wait
//    }
//
//    glfwTerminate();
//
//    return 0;
//}