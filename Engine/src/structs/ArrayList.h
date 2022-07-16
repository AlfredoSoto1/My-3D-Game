#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

namespace structs {

	template <typename Object>
	class ArrayList {
	public:

		ArrayList() : 
			fixedSize(10), pointer(0), currentList(nullptr), temporalList(nullptr) {

		}

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

			currentList = nullptr;
			temporalList = nullptr;
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

		template<typename Type>
		void sort(void(*pivotReturn)(const Object&, int*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*)) {
			quicksort<Type>(pivotReturn, leftAndRight, currentList, 0, pointer - 1);
		}

		int getSize() const {
			return fixedSize * sizeof(Object);
		}

		int getLength() const {
			return pointer;
		}

		bool isEmpty() const {
			return pointer == 0;
		}

		Object* toArray() {
			Object* array = new Object[pointer];
			for (int i = 0; i < pointer; i++)
				array[i] = currentList[i];
			return array;
		}

	private:

		int pointer;
		int fixedSize;

		Object* currentList;
		Object* temporalList;

		void swapElement(Object* array, int index1, int index2) {
			Object temp = array[index1];
			array[index1] = array[index2];
			array[index2] = temp;
		}

		template<typename Type>
		void quicksort(void(*pivotReturn)(const Object&, Type*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*),
			Object* array, int lowIndex, int highIndex) {
			if (lowIndex >= highIndex)
				return;
			Type pivot = 0;
			pivotReturn(array[highIndex], &pivot);

			int leftPointer = lowIndex;
			int rightPointer = highIndex;

			while (leftPointer < rightPointer) {
				Type leftData = 0;
				Type rightData = 0;
				leftAndRight(array[leftPointer], array[rightPointer], &leftData, &rightData);

				while (leftData <= pivot && leftPointer < rightPointer)
					leftPointer++;
				while (rightData >= pivot && leftPointer < rightPointer)
					rightPointer--;
				swapElement(array, leftPointer, rightPointer);
			}
			Type leftData = 0;
			Type highData = 0;
			leftAndRight(array[leftPointer], array[highIndex], &leftData, &highData);
			if (leftData > highData) {
				swapElement(array, leftPointer, highIndex);
			}
			else {
				leftPointer = highIndex;
			}
			quicksort(pivotReturn, leftAndRight, array, lowIndex, leftPointer - 1);
			quicksort(pivotReturn, leftAndRight, array, leftPointer + 1, highIndex);
		}
	};
}

#endif // !_ARRAY_LIST_DEFINED
