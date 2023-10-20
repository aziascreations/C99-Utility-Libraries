#include "memutils.h"

#include <malloc.h>

#include "../src/platform.h"

size_t memUtils_getSize(void *ptr) {
	#if defined(NP_COMPILER_MSVC) || defined(NP_COMPILER_MINGW) || defined(NP_OS_WINDOWS)
		// Can work on MSVC, MinGW
		return _msize(ptr);
	#elif UNIX || defined(__GNUC__)
		// Can work on standard UNIX GCC, CLang, ???
		// Not present on all platforms https://www.gnu.org/software/gnulib/manual/html_node/malloc_005fusable_005fsize.html
		return malloc_usable_size(ptr);
	#else
		#error memutils.c requires to be compiled on either WIN32 or UNIX platforms !
		return 0;
	#endif
}
