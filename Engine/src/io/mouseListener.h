#pragma once


#ifndef _MOUSE_LISTENER_DEFINED
#define _MOUSE_LISTENER_DEFINED

namespace listener {

	class MouseListener {
	public:
		MouseListener(void* displayPtr);
		~MouseListener();

		bool isButtonDown(int button);
		//Add this in the future when is needed
		//bool isbuttonClicked(int button);
		//bool isbuttonReleased(int button);
		void getMouseSpeed(double* xSpeed, double* ySpeed);
		void getMousePosition(double* xpos, double* ypos);

		void speedToZero();

		//void* setCursorShape(unsigned int cursorShape);
		void setCursor(void* cursor);
		void destroy(void* cursor);
		void hideCursor();
		void grabCursor();
		void defaultCursor();
		void setCursorPosition(double x, double y);

		void(*mouseEnterCallbackAction)(void* displayPtr, int isinside) = nullptr;

	private:

		bool* buttons;

		double xPosition, yPosition;
		double xNormalized, yNormalized;
		double xScroll, yScroll;

		double lastXPosition, lastYPosition;

		int pathCount;

		const char** droppedPaths;

		void* displayPtr;

	};

}

#endif // !_MOUSE_LISTENER_DEFINED
