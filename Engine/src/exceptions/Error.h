#pragma once

#ifndef _ERROR_DEFINED
#define _ERROR_DEFINED

namespace error {
	
	void glClearError();
	void glCheckError();

	void throwOutBoundsError(unsigned int offNumber, unsigned int limit);
}

#endif // !_ERROR_DEFINED
