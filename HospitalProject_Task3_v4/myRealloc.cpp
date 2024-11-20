#include "myRealloc.h"

// Custom implementation of the realloc function for memory reallocation.
void* myRealloc::myReallocFunc(void* ptr, unsigned long newSize, unsigned long oldSize)
{
	void* newPtr;
	if (newSize == 0)
		newPtr = nullptr;
	else
	{
		newPtr = new BYTE[newSize];
		if (oldSize > 0)
			memcpy(newPtr, ptr, ((newSize < oldSize) ? newSize : oldSize));
	}
	delete[] ptr;
	return newPtr;
}