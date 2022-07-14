#pragma once

#ifndef _DISPLAY_DEFINED
#define _DISPLAY_DEFINED

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphics {

	class Display {
	public:

		Display();
		Display(const char* title, int width, int height);
		~Display();

		void close();
		void restore();
		void minimize();
		void maximize();
		void requestAttention();
		void centerCursorOnLaunch();

		void setTitle(const char* title);

		void setSize(int width, int height);
		void setPosition(int x, int y);

		void setAlwaysOnTop(bool isAlwaysOnTop);
		void setResizable(bool isResizable);
		void setDecorated(bool isDecorated);
		void setVisible(bool isVisible);
		void setFullscreen(bool isFullscreen);

		void setTransparent(float transparency);

		void build(int(*init)(), int(*update)(), int(*dispose)());

	private:

		const char* title;

		int xpos, ypos;
		int width, height;

		int frames;

		double time;

		float transparency = 0.0f;

		bool stillActive = true;
		bool isAlwaysOnTop = false;
		bool dynamicUpdate = false;
		bool isDecorated = true;
		bool isVisible = true;
		bool isResizable = true;
		bool isFullscreen = false;
		bool isIconified = false;
		bool isMaximized = false;
		bool isCursorCentered = false;
		bool hasResized = false;

		GLFWwindow* window;

		void createContextDisplay();

		void displayFrames();

		void preprocessPrepare();
		void centerWindow();
		void processPrepare();
	};
}

#endif // !_DISPLAY_DEFINED
