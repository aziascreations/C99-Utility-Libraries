#include "utils.h"

// Helps fix issues with missing symbol in MSVCRT builds
// Source: https://stackoverflow.com/a/1583220
#include "../platform.h"
#if defined(NP_OS_WINDOWS)
	int _fltused = 0;
#endif

float hashmap_getLoadFactor(HashMap *hashmap) {
	return (float) hashmap->entryCount / (float) hashmap->capacity;
}
