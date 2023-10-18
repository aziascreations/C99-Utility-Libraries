#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "../../src/platform.h"

#include "../assert.h"
#include "../memutils.h"

#include "../../src/text.h"

static const wchar_t *text_01 = L"Hello world !";

int main(void) {
	// Preparing temporary variable.
	wchar_t *tmpCopy = NULL;
	
	#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
	assert_warn(true, "Tested on C11 variant, C99 wasn't tested !")
	#else
	assert_warn(true, "Tested on C99 variant, C11 wasn't tested !")
	#endif
	
	
	// Testing with simple function
	tmpCopy = text_copyW(text_01);
	
	assert(tmpCopy != NULL, "Simple copy isn't NULL.")
	assert(wcslen(tmpCopy) == 13, "Simple copy has `13` chars.")
	assert(wcscmp(text_01, tmpCopy) == 0, "Simple copy is the same as the original.")
	assert(text_01 != tmpCopy, "Simple copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(wchar_t) * (13 + 1), "Simple copy's memory size is `>=14` wchar long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(wchar_t) * (13 + 1), "Simple copy's memory size is `==14` wchar long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on full string
	tmpCopy = text_copyW_s(text_01, wcslen(text_01));
	
	assert(tmpCopy != NULL, "Complex full copy isn't NULL.")
	assert(wcslen(tmpCopy) == 13, "Complex full copy has `13` chars.")
	assert(wcscmp(text_01, tmpCopy) == 0, "Complex full copy is the same as the original.")
	assert(text_01 != tmpCopy, "Complex full copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(wchar_t) * (13 + 1), "Complex full copy's memory size is `>=14` wchar long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(wchar_t) * (13 + 1), "Complex full copy's memory size is `==14` wchar long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on undersized string
	tmpCopy = text_copyW_s(text_01, wcslen(text_01) - 5);
	
	assert(tmpCopy != NULL, "Complex undersized copy isn't NULL.")
	assert(wcslen(tmpCopy) == 8, "Complex undersized copy has `8` chars.")
	assert(wcscmp(text_01, tmpCopy) != 0, "Complex undersized copy isn't the same as the original.")
	assert(wcscmp(L"Hello wo", tmpCopy) == 0, "Complex undersized copy is the expected subset of the original.")
	assert(text_01 != tmpCopy, "Complex undersized copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(wchar_t) * (8 + 1), "Complex undersized copy's memory size is `>=9` wchar long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(wchar_t) * (8 + 1), "Complex undersized copy's memory size is `==9` wchar long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on undersized string
	tmpCopy = text_copyW_s(text_01, 999);
	
	assert(tmpCopy != NULL, "Complex oversized copy isn't NULL.")
	assert(wcslen(tmpCopy) == 13, "Complex oversized copy has `13` chars.")
	assert(wcscmp(text_01, tmpCopy) == 0, "Complex oversized copy is the same as the original.")
	assert(text_01 != tmpCopy, "Complex oversized copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(wchar_t) * (13 + 1), "Complex oversized copy's memory size is `>=14` wchar long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(wchar_t) * (13 + 1), "Complex oversized copy's memory size is `==14` wchar long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
	assert_warn(true, "Tested on C11 variant, C99 wasn't tested !")
	#else
	assert_warn(true, "Tested on C99 variant, C11 wasn't tested !")
	#endif
	
	return 0;
}
