#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

namespace structs {

	template <typename Object>
	class ArrayList {
	public:

		ArrayList();

		ArrayList(int fixedSize) :
		fixedSize(fixedSize) {

		}

		~ArrayList() {
			clear();
		}

		void clear() {
			pointer = 0;
			fixedSize = 10;

			if (currentList != nullptr)
				delete[] currentList;
			if (temporalList != nullptr)
				delete[] temporalList;

			temporalList = nullptr;
			currentList = nullptr;
		}

		void remove(int index) {
			if (index >= pointer || index < 0) {
				//printf("Array index out bounds!, index: %i, size: %i \n", index, pointer);
				return;
			}
			for (int i = index; i < pointer - 1; i++) {
				currentList[i] = currentList[i + 1];
			}
			pointer--;
		}

		Object* get(int index) {
			if (index >= pointer || index < 0) {
				//printf("Array index out bounds!, index: %i, size: %i \n", index, pointer);
				return nullptr;
			}
			return &currentList[index];
		}

		void insert(int index, const Object& obj) {
			if (index > pointer || index < 0) {
				//printf("Array index out bounds!, index: %i, size: %i \n", index, pointer);
				return;
			}

			if (pointer >= fixedSize) {
				temporalList = currentList;
				currentList = new Object[fixedSize * 2];

				for (int i = 0; i < fixedSize + 1; i++) {
					if (i > index) {
						currentList[i] = temporalList[i - 1];
					}
					else if (i == index) {
						currentList[i] = obj;
					}
					else {
						currentList[i] = temporalList[i];
					}
				}
				fixedSize *= 2;
				delete[] temporalList;
				temporalList = nullptr;
			}
			else {
				for (int i = pointer; i > index; i--)
					currentList[i] = currentList[i - 1];
				currentList[index] = obj;
			}
			pointer++;
		}

		void add(const Object& obj) {
			if (currentList == nullptr)
				currentList = new Object[fixedSize];

			if (pointer >= fixedSize) {
				temporalList = currentList;
				currentList = new Object[fixedSize * 2];

				for (int i = 0; i < fixedSize; i++)
					currentList[i] = temporalList[i];
				fixedSize *= 2;
				delete[] temporalList;
				temporalList = nullptr;
			}
			currentList[pointer++] = obj;
		}

		void sort() {

		}

		int getSize() {
			return fixedSize * sizeof(Object);
		}

		int getLength() {
			return pointer;
		}

		bool isEmpty() {
			return pointer == 0;
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
