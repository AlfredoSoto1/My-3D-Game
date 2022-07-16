#pragma once

#ifndef _ARRAY_LIST_DEFINED
#define _ARRAY_LIST_DEFINED

namespace structs {

	template <typename Object>
	class ArrayList {
	public:

		ArrayList() {

		}

		ArrayList(int fixedSize) {

		}

		~ArrayList() {

		}

	private:

		int fixedSize;

		Object* currentList;
		Object* temporalList;
	};
}

#endif // !_ARRAY_LIST_DEFINED
