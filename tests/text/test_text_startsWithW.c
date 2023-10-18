#include <stdio.h>
#include <wchar.h>

#include "../assert.h"

#include "../../src/text.h"

// Test strings
static const wchar_t *text_01 = L"Hello world !";

int main(void) {
	// Basic tests
	assert(text_startsWithW(text_01, L"Hello w"),
		   "Valid test #1")
	assert(text_startsWithW(text_01, L"Hello world !"),
		   "Valid test #2 - Full string")
	assert(text_startsWithW(text_01, L"Hello "),
		   "Valid test #3 - Ending with space")
	assert(text_startsWithW(text_01, L""),
		   "Valid test #4 - Empty prefix")
	
	assert(!text_startsWithW(text_01, L"Ree !"),
		   "Invalid test #1")
	assert(!text_startsWithW(text_01, L"HelLo"),
		   "Invalid test #2 - Text casing check")
		   
	// Edge-cases tests
	assert(text_startsWithW(text_01, L"Hello \0world !"),
		   "Edge-case test #1 - Middle NULL with same string")
	assert(text_startsWithW(text_01, L"Hello \0planet earth !"),
		   "Edge-case test #2 - Middle NULL with invalid end")
	assert(!text_startsWithW(text_01, L"Howdy \0world !"),
		   "Edge-case test #3 - Middle NULL with invalid start")
	
	return 0;
}
