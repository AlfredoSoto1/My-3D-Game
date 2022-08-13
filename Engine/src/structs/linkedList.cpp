//#include "linkedList.h"
//#include "../exceptions/Error.h"
//
//#ifndef _IMPLEMENTATION_DEFINED_ARRAY_LIST
////#define _IMPLEMENTATION_DEFINED_ARRAY_LIST
//
//using namespace structs;
//
//template<class Object>
//LinkedList<Object>::LinkedList() {
//
//}
//
//template<class Object>
//LinkedList<Object>::~LinkedList() {
//	clear();
//}
//
//template<class Object>
//Object* LinkedList<Object>::get(unsigned int index) const {
//	if (index > elementCount || index < 0) {
//		error::throwOutBoundsError(index, elementCount);
//		return nullptr;
//	}
//
//	if (current == nullptr)
//		current = first;
//	for (int i = 0; i < index - currentElement; i++)
//		current = current->next;
//	for (int i = 0; i < currentElement - index; i++)
//		current = current->prev;
//	currentElement = index;
//	return &(current->data);
//}
//
//template<class Object>
//Object* LinkedList<Object>::find(const Object& object) const {
//
//}
//
//template<class Object>
//bool LinkedList<Object>::contains(const Object& object) const {
//
//}
//
//template<class Object>
//int LinkedList<Object>::indexOf(const Object& object) const {
//
//}
//
//template<class Object>
//bool LinkedList<Object>::isEmpty() const {
//	return elementCount == 0;
//}
//
//template<class Object>
//unsigned int LinkedList<Object>::getCount() const {
//	return elementCount;
//}
//
//template<class Object>
//void LinkedList<Object>::add(const Object& object) {
//	if (last == nullptr) {
//		last = new Node();
//		last->data = obj;
//		first = last;
//		elementCount++;
//	}
//	else {
//		last->next = new Node();
//		last->next->data = obj;
//		last->next->prev = last;
//		last = last->next;
//		elementCount++;
//	}
//}
//
//template<class Object>
//void LinkedList<Object>::replace(unsigned int index, const Object& object) {
//
//}
//
//template<class Object>
//void LinkedList<Object>::remove(unsigned int index) {
//	if (index > elementCount || index < 0) {
//		error::throwOutBoundsError(index, elementCount);
//		return nullptr;
//	}
//
//	if (current == nullptr)
//		current = first;
//
//	for (int i = 0; i < index - currentElement; i++)
//		current = current->next;
//	for (int i = 0; i < currentElement - index; i++)
//		current = current->prev;
//	currentElement = index;
//
//	Node* pNext = current->next;
//	Node* pPrev = current->prev;
//
//	delete current;
//
//	if (pPrev == nullptr) {
//		current = pNext;
//	}
//	else if (pNext == nullptr) {
//		current = pPrev;
//		currentElement--;
//	}
//	else {
//		pPrev->next = pNext;
//		pNext->prev = pPrev;
//		current = pNext;
//	}
//	elementCount--;
//}
//
//template<class Object>
//void LinkedList<Object>::insert(unsigned int index, const Object& object) {
//	if (index > elementCount || index < 0) {
//		error::throwOutBoundsError(index, elementCount);
//		return;
//	}
//
//	if (current == nullptr)
//		current = first;
//
//	for (int i = 0; i < index - currentElement; i++)
//		current = current->next;
//	for (int i = 0; i < currentElement - index; i++)
//		current = current->prev;
//
//	currentElement = index;
//
//	Node* pNext = current;
//	Node* pPrev = current->prev;
//
//	current = new Node();
//	current->data = obj;
//
//	if (pPrev == nullptr) {
//		first = current;
//		current->next = pNext;
//		pNext->prev = current;
//	}
//	else {
//		pPrev->next = current;
//		current->prev = pPrev;
//	}
//
//	if (pNext == nullptr) {
//		last = current;
//		pPrev->next = current;
//		current->prev = pPrev;
//	}
//	else {
//		current->next = pNext;
//		pNext->prev = current;
//	}
//	elementCount++;
//}
//
//template<class Object>
//void LinkedList<Object>::clear() {
//	Node* count = first;
//	for (int i = 0; i < elementCount; i++) {
//		Node* curr = count->next;
//		delete count;
//		count = curr;
//	}
//	last = nullptr;
//	first = nullptr;
//	current = nullptr;
//
//	elementCount = 0;
//	currentElement = 0;
//}
//
//#endif