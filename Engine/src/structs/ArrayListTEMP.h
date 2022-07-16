#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

#include <stdio.h>

namespace strct {

	template <typename Object>
	class ArrayList {
	private:
		Object* temp_list;
		Object* current_list;

		int pointer = 0;//size of list
		int initialSize = 10;//size of inner list array

		void swapElement(Object* _array, int _index1, int _index2) {
			Object temp = _array[_index1];
			_array[_index1] = _array[_index2];
			_array[_index2] = temp;
		}

		template<typename Type>
		void quicksort(void(*_pivotReturn)(const Object&, Type*), void(*_leftAndRight)(const Object&, const Object&, Type*, Type*),
			Object* _array, int lowIndex, int highIndex) {
			if (lowIndex >= highIndex)
				return;
			Type pivot = 0;
			_pivotReturn(_array[highIndex], &pivot);

			int leftPointer = lowIndex;
			int rightPointer = highIndex;

			while (leftPointer < rightPointer) {
				Type leftData = 0;
				Type rightData = 0;
				_leftAndRight(_array[leftPointer], _array[rightPointer], &leftData, &rightData);

				while (leftData <= pivot && leftPointer < rightPointer)
					leftPointer++;
				while (rightData >= pivot && leftPointer < rightPointer)
					rightPointer--;
				swapElement(_array, leftPointer, rightPointer);
			}
			Type leftData = 0;
			Type highData = 0;
			_leftAndRight(_array[leftPointer], _array[highIndex], &leftData, &highData);
			if (leftData > highData) {
				swapElement(_array, leftPointer, highIndex);
			}
			else {
				leftPointer = highIndex;
			}
			quicksort(_pivotReturn, _leftAndRight, _array, lowIndex, leftPointer - 1);
			quicksort(_pivotReturn, _leftAndRight, _array, leftPointer + 1, highIndex);
		}

	public:
		ArrayList() {}
		ArrayList(int initialSize) : initialSize(initialSize) {}
		~ArrayList() {
			clear();
		}

		/* EXAMPLE */
		//model.vboObjectList.bubbleSort([](const memory::Model::VBO& _left, const memory::Model::VBO& _right) {
		//	return _left.dimension > _right.dimension;
		//});

		//model.vboObjectList.quicksort<int>([](const memory::Model::VBO& _pivot, int* _rPivot) {
		//	*_rPivot = _pivot.dimension;
		//}, [](const memory::Model::VBO& _left, const memory::Model::VBO& _right, int* _rLeft, int* _rRight) {
		//	*_rLeft = _left.dimension;
		//	*_rRight = _right.dimension;
		//});

		//Sorts list depending of its content
		//algorithm used to sort: quick sort
		template<typename Type>
		void quicksort(void(*_pivotReturn)(const Object&, int*), void(*_leftAndRight)(const Object&, const Object&, Type*, Type*)) {
			quicksort<Type>(_pivotReturn, _leftAndRight, current_list, 0, pointer - 1);
		}

		//Sorts list depending of its content
		//algorithm used to sort: bubble sort
		void bubbleSort(bool(_compare)(const Object&, const Object&)) {
			for (int i = 0; i < pointer; i++) {
				for (int j = 1; j < (pointer - i); j++) {
					if (_compare(current_list[j - 1], current_list[j])) {
						//swap elements  
						Object temp = current_list[j - 1];
						current_list[j - 1] = current_list[j];
						current_list[j] = temp;
					}
				}
			}
		}

		//returns a pointer to a copy of the objects as an array
		Object* toArray() {
			Object* array = new Object[pointer];
			for (int i = 0; i < pointer; i++)
				array[i] = current_list[i];
			return array;
		}

		//checks if list is empty
		bool isEmpty() const {
			return pointer == 0;
		}

		//returns current list size
		int size() const {
			return pointer;
		}

		//returns current list occupation space in memory(elements)
		int occupationSize() const {
			return initialSize;
		}

		//adds a copy of _object
		void add(const Object& _object) {
			if (current_list == nullptr)
				current_list = new Object[initialSize];

			if (pointer >= initialSize) {
				temp_list = current_list;
				current_list = new Object[initialSize * 2];

				for (int i = 0; i < initialSize; i++)
					current_list[i] = temp_list[i];
				initialSize *= 2;
				delete[] temp_list;
				temp_list = nullptr;
			}
			current_list[pointer++] = _object;
		}

		//inserts a copy of _object to a specific _index
		void insert(const int _index, const Object& _object) {
			if (_index > pointer || _index < 0) {
				printf("Array index out bounds!, index: %i, size: %i \n", _index, pointer);
				return;
			}

			if (pointer >= initialSize) {
				temp_list = current_list;
				current_list = new Object[initialSize * 2];

				for (int i = 0; i < initialSize + 1; i++) {
					if (i > _index) {
						current_list[i] = temp_list[i - 1];
					}
					else if (i == _index) {
						current_list[i] = _object;
					}
					else {
						current_list[i] = temp_list[i];
					}
				}
				initialSize *= 2;
				delete[] temp_list;
				temp_list = nullptr;
			}
			else {
				for (int i = pointer; i > _index; i--)
					current_list[i] = current_list[i - 1];
				current_list[_index] = _object;
			}
			pointer++;
		}

		//returns a pointer of the _object in the list
		Object* get(const int _index) const {
			if (_index >= pointer || _index < 0) {
				printf("Array index out bounds!, index: %i, size: %i \n", _index, pointer);
				return nullptr;
			}
			return &current_list[_index];
		}

		//removes an _object from list
		void remove(const int _index) {
			if (_index >= pointer || _index < 0) {
				printf("Array index out bounds!, index: %i, size: %i \n", _index, pointer);
				return;
			}
			for (int i = _index; i < pointer - 1; i++)
			{
				current_list[i] = current_list[i + 1];
			}
			pointer--;
		}

		//clears list and resets pointers
		void clear() {
			pointer = 0;
			initialSize = 10;

			if (current_list != nullptr)
				delete[] current_list;
			if (temp_list != nullptr)
				delete[] temp_list;

			temp_list = nullptr;
			current_list = nullptr;
		}

	};
}

#endif // !_ARRAY_LIST_DEFINED
