#pragma once

#ifndef _DISPLAY_DEFINED
#define _DISPLAY_DEFINED

#define GLEW_STATIC

struct GLFWwindow;
struct GLFWmonitor;

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

		//display call functions
		void close();
		void focus();
		void restore();
		void minimize();
		void maximize();
		void requestAttention();
		void centerCursorOnLaunch();

		//display set funcitions
		void setTitle(const char* title);
		void setSize(int width, int height);
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

		static void build();

	private:

		const char* title;

		int idLocation;

		int xpos, ypos;
		int width, height;

		static int currentDisplaysRunning;

		//Display preferences
		int frames = 0;
		int targetFrames = VSYNC_FPS;
		int currentMonitor = 0;

		double lastTime = 0.0;
		double lastRefresh = 0.0;

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
		bool hasResized = false;
		bool isRunning = false;
		bool vsyncEnabled = true;
		bool waiting = true;
		bool hasInitiated = false;
		bool failedToCreate = false;

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

		void processFrames();

		static void run(Display* display);
	};
}

#endif // !_DISPLAY_DEFINED
