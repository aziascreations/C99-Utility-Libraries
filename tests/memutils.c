#include "memutils.h"

#include <malloc.h>

size_t memUtils_getSize(void *ptr) {
	#ifdef WIN32
		return _msize(ptr);
	#else
		#ifdef UNIX
			return malloc_usable_size(ptr);
		#else
			#error memutils.c requires to be compiled on either WIN32 or UNIX platforms !
			return 0;
		#endif
	#endif
}
