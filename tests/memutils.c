#include "memutils.h"

#include <malloc.h>

size_t memUtils_getSize(void *ptr) {
	#if WIN32 || defined(_MSC_VER)
		return _msize(ptr);
	#elif UNIX || defined(__GNUC__)
		return malloc_usable_size(ptr);
	#else
		#error memutils.c requires to be compiled on either WIN32 or UNIX platforms !
		return 0;
	#endif
}
