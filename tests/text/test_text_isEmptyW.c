#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Space-only tests
	assert(text_isEmptyW(L""),
		   "Empty string (true)")
	assert(text_isEmptyW(L" "),
		   "Single space string (true)")
	assert(text_isEmptyW(L"   "),
		   "Multi space string (true)")
	
	// Special characters without space
	assert(text_isEmptyW(L"\t"),
		   "Single tab string (true)")
	assert(text_isEmptyW(L"\r"),
		   "Single CR string (true)")
	assert(text_isEmptyW(L"\n"),
		   "Single LF string (true)")
	
	// Special characters without space
	assert(text_isEmptyW(L" \t "),
		   "Complex string with tab (true)")
	assert(text_isEmptyW(L" \r "),
		   "Complex string with CR (true)")
	assert(text_isEmptyW(L" \n "),
		   "Complex string with LF (true)")
	assert(text_isEmptyW(L" \r\n "),
		   "Complex string with CRLF (true)")
	
	// Non-empty strings
	assert(!text_isEmptyW(L"   123"),
		   "Non-empty string #1 (false)")
	assert(!text_isEmptyW(L"   \t123"),
		   "Non-empty string #2 (false)")
	assert(!text_isEmptyW(L"   \r\n123"),
		   "Non-empty string #3 (false)")
	
	// Edge-cases tests
	assert(text_isEmptyW(L"   \0 123"),
		   "Edge-case test #1 (true)")
	
	return 0;
}
