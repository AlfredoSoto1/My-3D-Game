
#include "graphics/Display.h"

#include <iostream>

int init();
int update();
int dispose();

int main() {

	graphics::Display* window = new graphics::Display("Window", 1280, 720);
	window->build(&init, &update, &dispose);

	return 0;
}

//initiate GLFW/OpenGL context
int init() {

	std::cout << "init has begun" << std::endl;

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





//#define GLEW_STATIC

//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//#include<iostream>
//int main(void) {
//
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
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
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}