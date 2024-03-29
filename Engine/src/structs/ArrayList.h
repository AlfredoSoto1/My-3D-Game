#pragma once

#ifndef _ARRAY_LIST_DEFINED1
#define _ARRAY_LIST_DEFINED1

namespace structs {

	template<class Object>
	class ArrayList {
	public:
		ArrayList();
		ArrayList(unsigned int resizeStep);
		~ArrayList();

		//accessor
		Object* get(unsigned int index) const;
		Object* find(const Object& object);
		bool contains(const Object& object);
		int indexOf(const Object& object);

		bool isEmpty() const;
		unsigned int getCount() const;

		//modifiers
		void add(const Object& object);
		void replace(unsigned int index, const Object& object);
		void remove(unsigned int index);
		void insert(unsigned int index, const Object& object);
		void clear();

		template<class Type>
		void sort(void(*pivotReturn)(const Object&, int*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*));

	private:
		unsigned int arrayLength;
		unsigned int elementCount;
		unsigned int arrayResizeStep;

		Object* data;

		void resize();
		bool needToResize();

		template<class Type>
		void quicksort(void(*pivotReturn)(const Object&, Type*), void(*leftAndRight)(const Object&, const Object&, Type*, Type*),
			Object* array, int lowIndex, int highIndex);
		void swapElement(Object* array, int index1, int index2);
	};

}
#include "arrayList.cpp"

#endif // _ARRAY_LIST_DEFINED