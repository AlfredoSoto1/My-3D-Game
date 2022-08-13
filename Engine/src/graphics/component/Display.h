#pragma once

#ifndef _DISPLAY_DEFINED
#define _DISPLAY_DEFINED

#define GLEW_STATIC

#ifndef _GLFW_POINTERS_DEFINED
#define _GLFW_POINTERS_DEFINED

typedef struct GLFWwindow GLFWwindow;
struct GLFWmonitor;

#endif // !_GLFW_POINTERS_DEFINED


#include "../../io/windowListener.h"
#include "../../io/mouseListener.h"
#include "../../io/keyListener.h"

namespace graphics {

	class Display {
	public:

		enum RefreshRate {
			UNLIMITED_FPS = 0,
			VSYNC_FPS = 1
		};

		Display();
		Display(const char* title, int width, int height);
		~Display();

		//operator overloading
		operator GLFWwindow* ();

		//display call functions
		void close();
		void focus();
		void restore();
		void minimize();
		void maximize();
		void requestAttention();
		void centerCursorOnLaunch();

		volatile bool resized();

		//display set funcitions
		void setTitle(const char* title);
		void setSize(int width, int height);
		void setDimensions(int width, int height);
		void setPosition(int x, int y);
		void setVisible(bool isVisible);
		void setTransparent(float transparency);
		void setFuntions(int(*init)(), int(*update)(), int(*dispose)());
		void setFullscreen(bool isFullscreen);
		void setTargetFps(int targetFrames);
		void setStartUpMonitor(int startUpMonitor);

		//display attributes
		void setAlwaysOnTop(bool isAlwaysOnTop);
		void setResizable(bool isResizable);
		void setDecorated(bool isDecorated);
		void setDynamicUpdate(bool isDynamicallyUpdated);

		//return types
		bool isDynamicallyUpdated();
		void getDimensions(int* width, int* height);

		//renders or refreshes display
		//this function must be called inside a context
		void render(int isOnCallback = 0);

		//static functions
		static void build();

		listener::WindowListener* windowListener;
		listener::MouseListener* mouseListener;
		listener::KeyListener* keyListener;

		double timeDifference = 0.0;

	private:

		const char* title;

		int idLocation;
		 
		int xpos, ypos;
		int width, height;

		volatile static int currentDisplaysRunning;

		//Display preferences
		int frames = 0;
		int targetFrames = VSYNC_FPS;
		int currentMonitor = 0;

		double lastTime = 0.0;
		double lastRefresh = 0.0;
		double lastTimeDifference = 0.0;

		//Window Display transparency
		float transparency = 0.0f;

		//pre-process booleans
		bool isIconified = false;
		bool isMaximized = false;
		bool isAlwaysOnTop = false;
		bool dynamicUpdate = false;
		bool isCursorCentered = false;
		
		//runtime booleans
		bool isVisible = true;
		bool isResizable = true;
		bool isDecorated = true;
		bool isFullscreen = false;
		volatile bool isRunning = false;
		volatile bool vsyncEnabled = true;
		volatile bool waiting = true;
		volatile bool hasInitiated = false;
		volatile bool failedToCreate = false;
		volatile bool hasResized = false;

		//integrated functions
		int(*init)();
		int(*update)();
		int(*dispose)();

		GLFWwindow* window;
		GLFWmonitor* startUpMonitor;

		//Display creation functions
		void createDisplay();
		void renderDisplay();
		void setWindowHints();
		bool createWindow();
		void setWindowAttribs();
		void centerWindow();
		bool initGLEW();

		//functions
		void processFrames();

		static void run(Display* display);
	};
}

#endif // !_DISPLAY_DEFINED
