#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Space-only tests
	assert(text_isEmpty(""),
		   "Empty string (true)")
	assert(text_isEmpty(" "),
		   "Single space string (true)")
	assert(text_isEmpty("   "),
		   "Multi space string (true)")
	
	// Special characters without space
	assert(text_isEmpty("\t"),
		   "Single tab string (true)")
	assert(text_isEmpty("\r"),
		   "Single CR string (true)")
	assert(text_isEmpty("\n"),
		   "Single LF string (true)")
	
	// Special characters without space
	assert(text_isEmpty(" \t "),
		   "Complex string with tab (true)")
	assert(text_isEmpty(" \r "),
		   "Complex string with CR (true)")
	assert(text_isEmpty(" \n "),
		   "Complex string with LF (true)")
	assert(text_isEmpty(" \r\n "),
		   "Complex string with CRLF (true)")
	
	// Non-empty strings
	assert(!text_isEmpty("   123"),
		   "Non-empty string #1 (false)")
	assert(!text_isEmpty("   \t123"),
		   "Non-empty string #2 (false)")
	assert(!text_isEmpty("   \r\n123"),
		   "Non-empty string #3 (false)")
		   
	// Edge-cases tests
	assert(text_isEmpty("   \0 123"),
		   "Edge-case test #1 (true)")
	
	return 0;
}
