#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

namespace list {

	template<class Object>
	class ArrayList {
	public:
		//constructors
		ArrayList();
		ArrayList(unsigned int resizeStep);
		~ArrayList();

		//accessors
		Object* get(unsigned int index) const;
		int indexOf(const Object& object) const;
		bool contains(const Object& object) const;

		bool isEmpty() const;
		unsigned int getCount() const;

		//modifiers
		void add(const Object& object);
		void replace(unsigned int index, const Object& object);
		void remove(unsigned int index);
		void insert(unsigned int index, const Object& object);
		void clear();

	private:
		unsigned int arrayLength;
		unsigned int elementCount;
		unsigned int arrayResizeStep;

		Object* data;

		void resize();
		bool needToResize();

		int find(const Object& object);
	};

}
#include "arrayList.cpp"

#endif // _ARRAY_LIST_DEFINED