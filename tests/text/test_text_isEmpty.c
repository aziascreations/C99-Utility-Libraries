#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Preliminary tests
	assert(text_isEmptyA(NULL),
		   "Returns `true` if `string` is NULL")
	   
	// Space-only tests
	assert(text_isEmptyA(""),
		   "Empty string (true)")
	assert(text_isEmptyA(" "),
		   "Single space string (true)")
	assert(text_isEmptyA("   "),
		   "Multi space string (true)")
	
	// Special characters without space
	assert(text_isEmptyA("\t"),
		   "Single tab string (true)")
	assert(text_isEmptyA("\r"),
		   "Single CR string (true)")
	assert(text_isEmptyA("\n"),
		   "Single LF string (true)")
	
	// Special characters without space
	assert(text_isEmptyA(" \t "),
		   "Complex string with tab (true)")
	assert(text_isEmptyA(" \r "),
		   "Complex string with CR (true)")
	assert(text_isEmptyA(" \n "),
		   "Complex string with LF (true)")
	assert(text_isEmptyA(" \r\n "),
		   "Complex string with CRLF (true)")
	
	// Non-empty strings
	assert(!text_isEmptyA("   123"),
		   "Non-empty string #1 (false)")
	assert(!text_isEmptyA("   \t123"),
		   "Non-empty string #2 (false)")
	assert(!text_isEmptyA("   \r\n123"),
		   "Non-empty string #3 (false)")
		   
	// Edge-cases tests
	assert(text_isEmptyA("   \0 123"),
		   "Edge-case test #1 (true)")
	
	return 0;
}
