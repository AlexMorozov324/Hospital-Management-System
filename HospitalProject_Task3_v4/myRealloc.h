#ifndef __myRealloc_H
#define __myRealloc_H

#include <string.h>

typedef unsigned char BYTE;

class myRealloc
{
public:
	static void* myReallocFunc(void* ptr, unsigned long newSize, unsigned long oldSize);
};

#endif // __myRealloc_H
