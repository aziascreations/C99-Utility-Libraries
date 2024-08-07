#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Preliminary tests
	assert(text_isEmpty(NULL),
		   "Returns `true` if `string` is NULL")
	   
	// Space-only tests
	assert(text_isEmpty(TEXT("")),
		   "Empty string (true)")
	assert(text_isEmpty(TEXT(" ")),
		   "Single space string (true)")
	assert(text_isEmpty(TEXT("   ")),
		   "Multi space string (true)")
	
	// Special characters without space
	assert(text_isEmpty(TEXT("\t")),
		   "Single tab string (true)")
	assert(text_isEmpty(TEXT("\r")),
		   "Single CR string (true)")
	assert(text_isEmpty(TEXT("\n")),
		   "Single LF string (true)")
	
	// Special characters without space
	assert(text_isEmpty(TEXT(" \t ")),
		   "Complex string with tab (true)")
	assert(text_isEmpty(TEXT(" \r ")),
		   "Complex string with CR (true)")
	assert(text_isEmpty(TEXT(" \n ")),
		   "Complex string with LF (true)")
	assert(text_isEmpty(TEXT(" \r\n ")),
		   "Complex string with CRLF (true)")
	
	// Non-empty strings
	assert(!text_isEmpty(TEXT("   123")),
		   "Non-empty string #1 (false)")
	assert(!text_isEmpty(TEXT("   \t123")),
		   "Non-empty string #2 (false)")
	assert(!text_isEmpty(TEXT("   \r\n123")),
		   "Non-empty string #3 (false)")
		   
	// Edge-cases tests
	assert(text_isEmpty(TEXT("   \0 123")),
		   "Edge-case test #1 (true)")
	
	return 0;
}
