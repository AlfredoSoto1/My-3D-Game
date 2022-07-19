#pragma once

#ifndef _WINDOW_LISTENER
#define _WINDOW_LISTENER

namespace listener {
	class WindowListener {
	public:
		WindowListener(void* displayPtr);

		int(*closeCallbackAction)(void* display) = nullptr;
		int(*onFocusCallbackAction)(void* display, int isFocused) = nullptr;
		int(*iconificationCallbackAction)(void* display, int isIconified) = nullptr;
		int(*maximizedCallbackAction)(void* display, int isMaximized) = nullptr;
	};
}

#endif // !_WINDOW_LISTENER
