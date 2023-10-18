#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

// Test strings
static const char *text_01 = "Hello world !";

int main(void) {
	// Preliminary tests
	assert(!text_startsWith(NULL, "Hello w"),
		   "Fails if `string` is NULL")
	assert(!text_startsWith(text_01, NULL),
		   "Fails if `prefix` is NULL")
	   
	// Basic tests
	assert(text_startsWith(text_01, "Hello w"),
		   "Valid test #1")
	assert(text_startsWith(text_01, "Hello world !"),
		   "Valid test #2 - Full string")
	assert(text_startsWith(text_01, "Hello "),
		   "Valid test #3 - Ending with space")
	assert(text_startsWith(text_01, ""),
		   "Valid test #4 - Empty prefix")
	
	assert(!text_startsWith(text_01, "Ree !"),
		   "Invalid test #1")
	assert(!text_startsWith(text_01, "HelLo"),
		   "Invalid test #2 - Text casing check")
		   
	// Edge-cases tests
	assert(text_startsWith(text_01, "Hello \0world !"),
		   "Edge-case test #1 - Middle NULL with same string")
	assert(text_startsWith(text_01, "Hello \0planet earth !"),
		   "Edge-case test #2 - Middle NULL with invalid end")
	assert(!text_startsWith(text_01, "Howdy \0world !"),
		   "Edge-case test #3 - Middle NULL with invalid start")
	
	return 0;
}
