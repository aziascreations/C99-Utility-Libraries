#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Preliminary tests
	assert(text_nextSpaceIndexA(NULL, 0) == 0,
		   "Returns `0` if `string` is NULL and `startIndex` is `0`")
	assert(text_nextSpaceIndexA(NULL, 42) == 0,
		   "Returns `0` if `string` is NULL and `startIndex` is positive")
	
	// Space-only tests
	assert(text_nextSpaceIndexA("", 0) == 0,
		   "Empty string starting at `0` returns `0`")
	assert(text_nextSpaceIndexA("", 99) == 0,
		   "Empty string starting at `99` returns `0`.")
	
	// String without any space
	assert(text_nextSpaceIndexA("abc132", 0) == 6,
		   "String without any text returns the '\\0'")
	
	// String with spaces
	assert(text_nextSpaceIndexA("abc 123 def", 0) == 3,
		   "Spaces string from `0` gives `3`")
	assert(text_nextSpaceIndexA("abc 123 def", 3) == 3,
		   "Spaces string from `3` gives `3`")
	assert(text_nextSpaceIndexA("abc 123 def", 4) == 7,
		   "Spaces string from `4` gives `7`")
	assert(text_nextSpaceIndexA("abc 123 def", 7) == 7,
		   "Spaces string from `7` gives `7`")
	assert(text_nextSpaceIndexA("abc 123 def", 8) == 11,
		   "Spaces string from `8` gives `11`")
	assert(text_nextSpaceIndexA("abc 123 def", 11) == 11,
		   "Spaces string from `11` gives `11`")
	assert(text_nextSpaceIndexA("abc 123 def", 12) == 11,
		   "Spaces string from `12` gives `11`")
	assert(text_nextSpaceIndexA("abc 123 def", 99) == 11,
		   "Spaces string from `99` gives `11`")
	
	return 0;
}
