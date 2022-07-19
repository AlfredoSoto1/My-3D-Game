
#include "graphics/component/Display.h"

#include <iostream>

int init();
int update();
int dispose();

int main() {

	graphics::Display* window1 = new graphics::Display("Window 1", 1280, 720);

	window1->setFuntions(&init, &update, &dispose);

	graphics::Display::build();

	delete window1;

	return 0;
}

//initiate GLFW/OpenGL context
int init() {
	
	return 0; //error code
}

//updates opengl scene
int update() {

	return 0; //error code
}

//disposes or cleans everything created in memory by the library
int dispose() {

	return 0; //error code
}




//
//#define GLEW_STATIC
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <thread>
//
//int stillRunning = 1;
//
//bool thread1Init = false;
//
//void runningThread1() {
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Could not initiate glew!" << std::endl;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//    thread1Init = true;
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glBegin(GL_TRIANGLES);
//
//        glVertex2f(-.5, 0.0);
//        glVertex2f(.5, 0.0);
//        glVertex2f(0.0, -.5);
//
//
//        glEnd();
//
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    stillRunning--;
//}
//
//void runningThread2() {
//    GLFWwindow* window;
//
//    while (!thread1Init);
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Could not initiate glew!" << std::endl;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glBegin(GL_TRIANGLES);
//
//        glVertex2f(-.5, 0.0);
//        glVertex2f(.5, 0.0);
//        glVertex2f(0.0, -.5);
//
//
//        glEnd();
//
//
//        /* Swap front and back buffers */
//        try {
//            glfwSwapBuffers(window);
//        }
//        catch (int numErr) {
//            std::cout << "Ex thread 2: " << numErr << std::endl;
//        }
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    stillRunning--;
//}
//
//int main(void) {
//
//    std::thread* thread1 = new std::thread(&runningThread1);
//    thread1->detach();
//   /* std::thread* thread2 = new std::thread(&runningThread2);
//    thread2->detach();*/
//
//    while (stillRunning > 0);
//
//    glfwTerminate();
//
//    delete thread1;
//    //delete thread2;
//
//    return 0;
//}