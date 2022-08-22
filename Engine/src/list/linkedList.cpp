#include "linkedList.h"
#include "../exceptions/Error.h"

#ifndef _IMPLEMENTATION_DEFINED_ARRAY_LIST
#define _IMPLEMENTATION_DEFINED_ARRAY_LIST

namespace list {
	/*
		Constructors
	*/
	template<class Object>
	LinkedList<Object>::LinkedList() {

	}

	template<class Object>
	LinkedList<Object>::~LinkedList() {
		clear();
	}

	/*
		private member functions
	*/

	/*
		find(const Object& obj) function returns a location-index to where
		is located in the list.
		This function will compare the bytes from "object" to every Object
		from the list. In case it doesn't find the "object" in the list,
		it will return -1.
	*/
	template<class Object>
	int LinkedList<Object>::find(const Object& object) {
		int sizeOf_Object = sizeof(object);
		char* rawBytes_Object = (char*)&object;

		if (first == nullptr)
			return -1;
		findNext = first;

		int verified = 0;
		for (unsigned int i = 0; i < elementCount; i++) {
			if (&(findNext->data) == &object)
				return i;
			int sizeOf_data = sizeof(findNext->data);
			char* rawBytes_data = (char*)&findNext->data;
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

			if (findNext->next == nullptr)
				break;
			findNext = findNext->next;
		}
		return -1;
	}

	/*
		public member functions
	*/

	/*
		next() function iterates to next element in the list.
	*/
	template<class Object>
	Object* LinkedList<Object>::next() const {
		if (first == nullptr)
			return nullptr;
		if (nextCurrent == nullptr)
			nextCurrent = first;
		Node* out = nextCurrent;
		nextCurrent = nextCurrent->next;
		return out;
	}

	/*
		hasNext() function returns true if has next element for iteration.
		It also iterates to next element in the list.
	*/
	template<class Object>
	bool LinkedList<Object>::hasNext() const {
		return next() != nullptr;
	}

	/*
		getFirst() function returns first element of list.
	*/
	template<class Object>
	Object* LinkedList<Object>::getFirst() const {
		return first;
	}

	/*
		getLast() function returns last element of list.
	*/
	template<class Object>
	Object* LinkedList<Object>::getLast() const {
		return last;
	}

	/*
		get(uint index) function returns
		a pointer to where is the data located at
	*/
	template<class Object>
	Object* LinkedList<Object>::get(unsigned int index) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		if (current == nullptr)
			current = first;
		for (int i = 0; i < (int)index - (int)currentElement; i++)
			current = current->next;
		for (int i = 0; i < (int)currentElement - (int)index; i++)
			current = current->prev;
		currentElement = index;
		return &(current->data);
	}

	/*
		indexOf(const Object& obj) function returns an integer
		with the location-index to where is the "object" in the list.
		In case of not finding any, return value will be -1.
	*/
	template<class Object>
	int LinkedList<Object>::indexOf(const Object& object) {
		return find(object);
	}

	/*
		contains(const Object& obj) returns a boolean
		to which it will be true if the list contains and "object".
	*/
	template<class Object>
	bool LinkedList<Object>::contains(const Object& object) {
		return find(object) != -1;
	}

	/*
		isEmpty() function returns true if list is
		empty.
	*/
	template<class Object>
	bool LinkedList<Object>::isEmpty() const {
		return elementCount == 0;
	}

	/*
		getCount() function returns unsigned int
		with the count of elements the list has in dynamic use.
	*/
	template<class Object>
	unsigned int LinkedList<Object>::getCount() const {
		return elementCount;
	}

	/*
		add(const Object& obj) function adds to list
		"object" when called
	*/
	template<class Object>
	void LinkedList<Object>::add(const Object& object) {
		if (last == nullptr) {
			last = new Node();
			last->data = object;
			first = last;
			elementCount++;
			return;
		}
		last->next = new Node();
		last->next->data = object;
		last->next->prev = last;
		last = last->next;
		elementCount++;
	}

	/*
		replace(uint index, const Object& obj) function
		replaces "object" from list to the location-index entered.
	*/
	template<class Object>
	void LinkedList<Object>::replace(unsigned int index, const Object& object) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		if (current == nullptr)
			current = first;
		for (int i = 0; i < (int)index - (int)currentElement; i++)
			current = current->next;
		for (int i = 0; i < (int)currentElement - (int)index; i++)
			current = current->prev;
		currentElement = index;
		current->data = object;
	}

	/*
		remove(uint index) function removes "object" from
		list at corresponding location-index.
	*/
	template<class Object>
	void LinkedList<Object>::remove(unsigned int index) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		if (current == nullptr)
			current = first;
		for (int i = 0; i < (int)index - (int)currentElement; i++)
			current = current->next;
		for (int i = 0; i < (int)currentElement - (int)index; i++)
			current = current->prev;
		currentElement = index;

		Node* pNext = current->next;
		Node* pPrev = current->prev;

		delete current;

		if (pPrev == nullptr) {
			current = pNext;
		}
		else if (pNext == nullptr) {
			current = pPrev;
			currentElement--;
		}
		else {
			pPrev->next = pNext;
			pNext->prev = pPrev;
			current = pNext;
		}
		elementCount--;
	}

	/*
		insert(uint index, const Object& object) function
		inserts an "object" to a location-index without replacing
		the "object" that might exist at location-index.
	*/
	template<class Object>
	void LinkedList<Object>::insert(unsigned int index, const Object& object) {
		if (index >= elementCount || index < 0)
			throw error::throwOutBoundsError(index, elementCount);
		if (current == nullptr)
			current = first;
		for (int i = 0; i < (int)index - (int)currentElement; i++)
			current = current->next;
		for (int i = 0; i < (int)currentElement - (int)index; i++)
			current = current->prev;

		currentElement = index;

		Node* pNext = current;
		Node* pPrev = current->prev;

		current = new Node();
		current->data = object;

		if (pPrev == nullptr) {
			first = current;
			current->next = pNext;
			pNext->prev = current;
		}
		else {
			pPrev->next = current;
			current->prev = pPrev;
		}

		if (pNext == nullptr) {
			last = current;
			pPrev->next = current;
			current->prev = pPrev;
		}
		else {
			current->next = pNext;
			pNext->prev = current;
		}
		elementCount++;
	}

	/*
		clear() function deletes all data from the list
		sets all values to default.
	*/
	template<class Object>
	void LinkedList<Object>::clear() {
		Node* count = first;
		for (int i = 0; i < elementCount; i++) {
			Node* curr = count->next;
			delete count;
			count = curr;
		}
		last = nullptr;
		first = nullptr;
		current = nullptr;

		elementCount = 0;
		currentElement = 0;
	}

}

#endif