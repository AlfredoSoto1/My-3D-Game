//#pragma once
//
//#ifndef _LINKED_LIST_DEFINED
//#define _LINKED_LIST_DEFINED
//
//namespace structs {
//
//	template <typename Object>
//	class LinkedList {
//	public:
//		LinkedList();
//		~LinkedList();
//
//		//accessor
//		Object* get(unsigned int index) const;
//		Object* find(const Object& object) const;
//		bool contains(const Object& object) const;
//		int indexOf(const Object& object) const;
//
//		bool isEmpty() const;
//		unsigned int getCount() const;
//
//		//modifiers
//		void add(const Object& object);
//		void replace(unsigned int index, const Object& object);
//		void remove(unsigned int index);
//		void insert(unsigned int index, const Object& object);
//		void clear();
//	private:
//		struct Node {
//			Object data;
//			Node* next = nullptr;
//			Node* prev = nullptr;
//		};
//		int elementCount;
//		int currentElement;
//
//		Node* last = nullptr;
//		Node* first = nullptr;
//		Node* current = nullptr;
//	};
//
//	template <typename Object>
//	class LinkedListOLD {
//	private:
//		struct Node {
//			Object data;
//			Node* next = nullptr;
//			Node* prev = nullptr;
//		};
//		int list_size;
//		int currentIndex;
//
//		Node* last = nullptr;
//		Node* first = nullptr;
//		Node* current = nullptr;
//	public:
//		LinkedList() {}
//		~LinkedList() {
//			clear();
//		}
//
//		//returns a pointer to a copy of the objects as an array
//		Object* toArray() {
//			int prevIndex = this->currentIndex;
//			Node* prevCurrent = this->current;
//			Object* array = new Object[list_size];
//			for (int i = 0; i < list_size; i++)
//				array[i] = *(this->get(i));
//			this->current = prevCurrent;
//			this->currentIndex = prevIndex;
//			return array;
//		}
//
//		//checks if list is empty
//		bool isEmpty() const {
//			return list_size == 0;
//		}
//
//		//returns size of list
//		int size() const {
//			return list_size;
//		}
//
//		//adds a copy of _object
//		void add(const Object& obj) {
//			if (last == nullptr) {
//				last = new Node();
//				last->data = obj;
//				first = last;
//				list_size++;
//			}
//			else {
//				last->next = new Node();
//				last->next->data = obj;
//				last->next->prev = last;
//				last = last->next;
//				list_size++;
//			}
//		}
//
//		//inserts a copy of _object to a specific _index
//		void insert(const int& index, const Object& obj) {
//			if (index >= list_size || index < 0) {
//				return;
//			}
//			if (current == nullptr) {
//				current = first;
//			}
//
//			for (int i = 0; i < index - currentIndex; i++)
//				current = current->next;
//			for (int i = 0; i < currentIndex - index; i++)
//				current = current->prev;
//
//			currentIndex = index;
//
//			Node* pNext = current;
//			Node* pPrev = current->prev;
//
//			current = new Node();
//			current->data = obj;
//
//			if (pPrev == nullptr) {
//				first = current;
//				current->next = pNext;
//				pNext->prev = current;
//			}
//			else {
//				pPrev->next = current;
//				current->prev = pPrev;
//			}
//
//			if (pNext == nullptr) {
//				last = current;
//				pPrev->next = current;
//				current->prev = pPrev;
//			}
//			else {
//				current->next = pNext;
//				pNext->prev = current;
//			}
//
//			list_size++;
//		}
//
//		//returns a pointer of the _object in the list
//		Object* get(const int& index) {
//			if (index >= list_size || index < 0) {
//				return nullptr;
//			}
//			if (current == nullptr)
//				current = first;
//
//			for (int i = 0; i < index - currentIndex; i++)
//				current = current->next;
//			for (int i = 0; i < currentIndex - index; i++)
//				current = current->prev;
//
//			currentIndex = index;
//			return &(current->data);
//		}
//
//		//removes an _object from list
//		void remove(const int& index) {
//			if (index >= list_size || index < 0) {
//				return;
//			}
//			if (current == nullptr)
//				current = first;
//
//			for (int i = 0; i < index - currentIndex; i++)
//				current = current->next;
//			for (int i = 0; i < currentIndex - index; i++)
//				current = current->prev;
//
//			currentIndex = index;
//
//			Node* pNext = current->next;
//			Node* pPrev = current->prev;
//
//			delete current;
//
//			if (pPrev == nullptr) {
//				current = pNext;
//			}
//			else if (pNext == nullptr) {
//				current = pPrev;
//				currentIndex--;
//			}
//			else {
//				pPrev->next = pNext;
//				pNext->prev = pPrev;
//				current = pNext;
//			}
//			list_size--;
//		}
//
//		//clears list and resets pointers
//		void clear() {
//			Node* count = first;
//			for (int i = 0; i < list_size; i++) {
//				Node* curr = count->next;
//				delete count;
//				count = curr;
//			}
//			last = nullptr;
//			first = nullptr;
//			current = nullptr;
//
//			list_size = 0;
//			currentIndex = 0;
//		}
//	};
//}
//
//#include "linkedList.cpp"
//
//#endif // !_LINKED_LIST_DEFINED
