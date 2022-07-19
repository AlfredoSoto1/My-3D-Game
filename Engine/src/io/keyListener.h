#pragma once

#ifndef _KEY_LISTENER_DEFINED
#define _KEY_LISTENER_DEFINED

namespace listener {

	class KeyListener {
	public:

		KeyListener(void* displayPtr);
		~KeyListener();

		bool isKeyDown(int key);
		bool isKeyToggled(int key);
		bool isKeyReleased(int key);

	private:

		bool* keys;

		bool toggled = false;
		bool released = false;
	};
}

#endif // !_KEY_LISTENER_DEFINED
