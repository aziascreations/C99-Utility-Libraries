#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/platform.h"

#include "../assert.h"
#include "../memutils.h"

#include "../../src/text.h"

static const char *text_01 = "Hello world !";

int main(void) {
	// Preliminary tests
	assert(text_copyA(NULL) == NULL,
		   "Returns NULL if `string` is NULL")
	assert(text_copyA_s(NULL, 42) == NULL,
		   "Returns NULL if `string` is NULL and length is positive")
		   
	// Preparing temporary variable.
	char *tmpCopy = NULL;
	
	
	// Testing with simple function
	tmpCopy = text_copyA(text_01);
	
	assert(tmpCopy != NULL, "Simple copy isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Simple copy has `13` chars.")
	assert(strcmp(text_01, tmpCopy) == 0, "Simple copy is the same as the original.")
	assert(text_01 != tmpCopy, "Simple copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Simple copy's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Simple copy's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on full string
	tmpCopy = text_copyA_s(text_01, strlen(text_01));
	
	assert(tmpCopy != NULL, "Complex full copy isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Complex full copy has `13` chars.")
	assert(strcmp(text_01, tmpCopy) == 0, "Complex full copy is the same as the original.")
	assert(text_01 != tmpCopy, "Complex full copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Complex full copy's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Complex full copy's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on undersized string
	tmpCopy = text_copyA_s(text_01, strlen(text_01) - 5);
	
	assert(tmpCopy != NULL, "Complex undersized copy isn't NULL.")
	assert(strlen(tmpCopy) == 8, "Complex undersized copy has `8` chars.")
	assert(strcmp(text_01, tmpCopy) != 0, "Complex undersized copy isn't the same as the original.")
	assert(strcmp("Hello wo", tmpCopy) == 0, "Complex undersized copy is the expected subset of the original.")
	assert(text_01 != tmpCopy, "Complex undersized copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (8 + 1), "Complex undersized copy's memory size is `>=9` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (8 + 1), "Complex undersized copy's memory size is `==9` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	// Testing with complex function on undersized string
	tmpCopy = text_copyA_s(text_01, 999);
	
	assert(tmpCopy != NULL, "Complex oversized copy isn't NULL.")
	assert(strlen(tmpCopy) == 13, "Complex oversized copy has `13` chars.")
	assert(strcmp(text_01, tmpCopy) == 0, "Complex oversized copy is the same as the original.")
	assert(text_01 != tmpCopy, "Complex oversized copy doesn't point to the original.")

	#ifndef NP_OS_WINDOWS
	assert(memUtils_getSize(tmpCopy) >= sizeof(char) * (13 + 1), "Complex oversized copy's memory size is `>=14` chars long.")
	#else
	assert(memUtils_getSize(tmpCopy) == sizeof(char) * (13 + 1), "Complex oversized copy's memory size is `==14` chars long.")
	#endif
	
	free(tmpCopy);
	tmpCopy = NULL;
	
	
	return 0;
}
