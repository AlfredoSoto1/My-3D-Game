#include "arrayList.h"
#include "../exceptions/Error.h"

#ifndef _IMPLEMENTATION_DEFINED_ARRAY_LIST
#define _IMPLEMENTATION_DEFINED_ARRAY_LIST

namespace list {
	/*
		Constructors
	*/
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

	/*
		private member functions		
	*/

	/*
		resize() function will double the size
		of the list when ever data_ptr[] array
		reaches max size.
	*/
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

	/*
		needToResize() function returns true if
		list needs to resize.
	*/
	template<class Object>
	bool ArrayList<Object>::needToResize() {
		return elementCount == arrayLength;
	}

	/*
		find(const Object& obj) function returns a location-index to where
		is located in the list.
		This function will compare the bytes from "object" to every Object
		from the list. In case it doesn't find the "object" in the list,
		it will return -1.
	*/
	template<class Object>
	int ArrayList<Object>::find(const Object& object) {
		int sizeOf_Object = sizeof(object);
		char* rawBytes_Object = (char*)&object;

		int verified = 0;
		for (unsigned int i = 0; i < elementCount; i++) {
			if (&data[i] == &object)
				return i;

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
				return i;
			else
				verified = 0;
		}
		return -1;
	}

	/*
		public member functions
	*/

	/*
		get(uint index) function returns
		a pointer to where is the data located at
	*/
	template<class Object>
	Object* ArrayList<Object>::get(unsigned int index) const {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		return &data[index];
	}

	/*
		contains(const Object& obj) returns a boolean
		to which it will be true if the list contains and "object".
	*/
	template<class Object>
	bool ArrayList<Object>::contains(const Object& object) const {
		return find(object) != -1;
	}

	/*
		indexOf(const Object& obj) function returns an integer
		with the location-index to where is the "object" in the list.
		In case of not finding any, return value will be -1.
	*/
	template<class Object>
	int ArrayList<Object>::indexOf(const Object& object) const {
		return find(object);
	}

	/*
		isEmpty() function returns true if list is
		empty.
	*/
	template<class Object>
	bool ArrayList<Object>::isEmpty() const {
		return elementCount == 0;
	}

	/*
		getCount() function returns unsigned int
		with the count of elements the list has in dynamic use.
	*/
	template<class Object>
	unsigned int ArrayList<Object>::getCount() const {
		return elementCount;
	}

	/*
		add(const Object& obj) function adds to list
		"object" when called
	*/
	template<class Object>
	void ArrayList<Object>::add(const Object& object) {
		if (needToResize())
			resize();
		data[elementCount++] = object;
	}

	/*
		replace(uint index, const Object& obj) function
		replaces "object" from list to the location-index entered.
	*/
	template<class Object>
	void ArrayList<Object>::replace(unsigned int index, const Object& object) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		data[index] = object;
	}

	/*
		remove(uint index) function removes "object" from
		list at corresponding location-index.
	*/
	template<class Object>
	void ArrayList<Object>::remove(unsigned int index) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		for (int i = index; i < elementCount - 1; i++)
			data[i] = data[i + 1];
		elementCount--;
	}

	/*
		insert(uint index, const Object& object) function
		inserts an "object" to a location-index without replacing
		the "object" that might exist at location-index.
	*/
	template<class Object>
	void ArrayList<Object>::insert(unsigned int index, const Object& object) {
		if (index > elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		if (needToResize())
			resize();
		for (int i = elementCount; i > index; i--)
			data[i] = data[i - 1];
		data[index] = object;
		elementCount++;
	}

	/*
		clear() function deletes all data from the list
		sets all values to default.
	*/
	template<class Object>
	void ArrayList<Object>::clear() {
		elementCount = 0;
		arrayLength = arrayResizeStep;
		if (data != nullptr)
			delete[] data;
		data = nullptr;
	}
}

#endif // !_IMPLEMENTATION_DEFINED
