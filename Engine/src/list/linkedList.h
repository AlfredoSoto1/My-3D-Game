#pragma once

#ifndef _LINKED_LIST_DEFINED
#define _LINKED_LIST_DEFINED

namespace list {
	template <typename Object>
	class LinkedList {
	public:
		//constructors
		LinkedList();
		~LinkedList();

		//accessor
		Object* next() const;
		bool hasNext() const;
		Object* getFirst() const;
		Object* getLast() const;
		Object* get(unsigned int index);
		int indexOf(const Object& object);
		bool contains(const Object& object);

		bool isEmpty() const;
		unsigned int getCount() const;

		//modifiers
		void add(const Object& object);
		void replace(unsigned int index, const Object& object);
		void remove(unsigned int index);
		void insert(unsigned int index, const Object& object);
		void clear();

	private:
		struct Node {
			Object data;
			Node* next = nullptr;
			Node* prev = nullptr;
		};

		int elementCount;
		int currentElement;

		Node* last = nullptr;
		Node* first = nullptr;
		Node* current = nullptr;
		Node* nextCurrent = nullptr;
		Node* findNext = nullptr;

		int find(const Object& object);
	};
}

#include "linkedList.cpp"

#endif // !_LINKED_LIST_DEFINED
