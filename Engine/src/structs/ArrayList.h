#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

namespace structs {

	template <typename Object>
	class ArrayList {
	public:

		ArrayList() {

		}

		ArrayList(int fixedSize) :
		fixedSize(fixedSize) {

		}

		~ArrayList() {
			clear();
		}

		void clear() {

		}

		void remove(int index) {

		}

		Object* get(int index) {
			return nullptr;
		}

		void insert(int index, const Object& obj) {

		}

		void add(const Object& obj) {
			if (currentList == nullptr)
				currentList = new Object[fixedSize];
			if (pointer >= fixedSize) {
				temporalList = currentList;
				currentList = new Object[fixedSize * 2];
			}
		}

		void sort() {

		}

		int getSize() {
			return 0;
		}

		int getLength() {
			return 0;
		}

		bool isEmpty() {
			return false;
		}

		Object* toArray() {
			return nullptr;
		}

	private:

		int pointer;
		int fixedSize = 10;

		Object* currentList;
		Object* temporalList;
	};
}

#endif // !_ARRAY_LIST_DEFINED
