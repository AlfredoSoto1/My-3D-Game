#include "arrayList.h"
#include "../exceptions/Error.h"

#ifndef _IMPLEMENTATION_DEFINED_ARRAY_LIST1
#define _IMPLEMENTATION_DEFINED_ARRAY_LIST1

using namespace structs;

template<class Object>
ArrayList<Object>::ArrayList() 
	: arrayLength(10), elementCount(0)
{
	arrayResizeStep = 10;
	resize();
}

template<class Object>
ArrayList<Object>::ArrayList(unsigned int resizeStep)
	: arrayLength(resizeStep), arrayResizeStep(resizeStep), elementCount(0)
{
	resize();
}

template<class Object>
ArrayList<Object>::~ArrayList() {
	clear();
}

template<class Object>
void ArrayList<Object>::resize() {
	if (data == nullptr) {
		data = new Object[arrayLength];
		return;
	}
	Object* tempData = new Object[arrayLength * 2];
	for (unsigned int i = 0; i < arrayLength; i++)
		tempData[i] = data[i];
	delete[] data;
	data = tempData;
	arrayLength *= 2;
}

template<class Object>
bool ArrayList<Object>::needToResize() {
	return elementCount == arrayLength;
}

template<class Object>
Object* ArrayList<Object>::get(unsigned int index) const {
	if (index > elementCount || index < 0) {
		error::throwOutBoundsError(index, elementCount);
		return nullptr;
	}
	return &data[index];
}

template<class Object>
Object* ArrayList<Object>::find(const Object& object) {
	int sizeOf_Object = sizeof(object);
	char* rawBytes_Object = (char*)&object;

	int verified = 0;
	for (unsigned int i = 0; i < elementCount; i++) {
		if (&data[i] == &object)
			return &data[i];

		int sizeOf_data = sizeof(data[i]);
		char* rawBytes_data = (char*)&data[i];
		if (sizeOf_data < sizeOf_Object)
			continue;
		//compares if object & data are the same
		for (int j = 0; j < sizeOf_Object; j++) {
			if (rawBytes_Object[j] != rawBytes_data[j])
				break;
			verified++;
		}
		//checks if the verified flag equals the size of object once compared
		if (verified == sizeOf_Object)
			return &data[i];
		else
			verified = 0;
	}
	return nullptr;
}

template<class Object>
bool ArrayList<Object>::contains(const Object& object) {
	Object* inListRef = find(object);
	if (inListRef != nullptr)
		return true;
	else
		return false;
}

template<class Object>
int ArrayList<Object>::indexOf(const Object& object) {
	Object* inListRef = find(object);
	if (inListRef == nullptr)
		return -1;
	if (isEmpty())
		return -1;
	int index = (int)inListRef - (int)&data[0];
	return index / sizeof(Object);
}

template<class Object>
bool ArrayList<Object>::isEmpty() const {
	return elementCount == 0;
}

template<class Object>
unsigned int ArrayList<Object>::getCount() const {
	return elementCount;
}

template<class Object>
void ArrayList<Object>::add(const Object& object) {
	if (needToResize())
		resize();
	data[elementCount++] = object;
}

template<class Object>
void ArrayList<Object>::replace(unsigned int index, const Object& object) {
	if (index > elementCount || index < 0) {
		error::throwOutBoundsError(index, elementCount);
		return nullptr;
	}
	data[index] = object;
}

template<class Object>
void ArrayList<Object>::remove(unsigned int index) {
	if (index > elementCount || index < 0) {
		error::throwOutBoundsError(index, elementCount);
		return nullptr;
	}
	for (int i = index; i < elementCount - 1; i++)
		data[i] = data[i + 1];
	elementCount--;
}

template<class Object>
void ArrayList<Object>::insert(unsigned int index, const Object& object) {
	if (index > elementCount || index < 0) {
		error::throwOutBoundsError(index, elementCount);
		return nullptr;
	}
	if (needToResize())
		resize();
	for (int i = elementCount; i > index; i--)
		data[i] = data[i - 1];
	data[index] = object;
	elementCount++;
}

template<class Object>
void ArrayList<Object>::clear() {
	elementCount = 0;
	arrayLength = arrayResizeStep;
	if (data != nullptr)
		delete[] data;
	data = nullptr;
}

template<typename Object>
template<typename Type>
void ArrayList<Object>::sort(void(*pivotReturn)(const Object&, int*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*)) {
	quicksort<Type>(pivotReturn, leftAndRight, data, 0, elementCount - 1);
}

template<typename Object>
void ArrayList<Object>::swapElement(Object* array, int index1, int index2) {
	Object temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

template<typename Object>
template<typename Type>
void ArrayList<Object>::quicksort(void(*pivotReturn)(const Object&, Type*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*),
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

#endif // !_IMPLEMENTATION_DEFINED
