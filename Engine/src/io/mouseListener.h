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

		void(*mouseEnterCallbackAction)(void* displayPtr, int isinside) = nullptr;

	private:

		bool* buttons;

		double xPosition, yPosition;
		double xNormalized, yNormalized;
		double xScroll, yScroll;

		double lastXPosition, lastYPosition;

		int pathCount;

		const char** droppedPaths;

	};

}

#endif // !_MOUSE_LISTENER_DEFINED
