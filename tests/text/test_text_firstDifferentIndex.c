#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Preliminary tests
	assert(text_firstDifferentIndex(NULL, ' ') == 0,
		   "Returns `0` if `string` is NULL and char is ' '")
	assert(text_firstDifferentIndex(NP_TEXT(" Hello :) "), '\0') == 0,
		   "Returns `0` if `string` isn't NULL and char is '\\0'")
	
	// Space-only tests
	assert(text_firstDifferentIndex(NP_TEXT("Hello world !"), ' ') == 0,
		   "Returns `0` if string doesn't have the undesired char at its beginning.")
	assert(text_firstDifferentIndex(NP_TEXT(" Hello world !"), ' ') == 1,
		   "Returns `1` if string has `1` undesired char at its beginning.")
	assert(text_firstDifferentIndex(NP_TEXT("   + Hello world !"), ' ') == 3,
		   "Returns `3` if string has `4` undesired char with the 4th separated its beginning.")
	
	// Symbols
	assert(text_firstDifferentIndex(NP_TEXT("Hello world !"), '_') == 0,
		   "Returns `0` if string doesn't have the undesired char at its beginning. (Using symbols)")
	assert(text_firstDifferentIndex(NP_TEXT("   Hello world !"), '_') == 0,
		   "Returns `0` if string doesn't have the undesired char at its beginning. (Using symbols)")
	assert(text_firstDifferentIndex(NP_TEXT("_Hello world !"), '_') == 1,
		   "Returns `1` if string has `1` undesired char at its beginning. (Using symbols)")
	assert(text_firstDifferentIndex(NP_TEXT("___+_Hello world !"), '_') == 3,
		   "Returns `3` if string has `4` undesired char with the 4th separated its beginning. (Using symbols)")
	
	// Special characters
	assert(text_firstDifferentIndex(NP_TEXT("Hello world !"), '\t') == 0,
		   "Returns `0` if string doesn't have the undesired char at its beginning. (Using \\t)")
	assert(text_firstDifferentIndex(NP_TEXT("   Hello world !"), '\t') == 0,
		   "Returns `0` if string doesn't have the undesired char at its beginning. (Using \\t)")
	assert(text_firstDifferentIndex(NP_TEXT("\tHello world !"), '\t') == 1,
		   "Returns `1` if string has `1` undesired char at its beginning. (Using \\t)")
	assert(text_firstDifferentIndex(NP_TEXT("\t\t\t \tHello world !"), '\t') == 3,
		   "Returns `3` if string has `4` undesired char with the 4th separated its beginning. (Using \\t)")
		   
	// Edge-cases
	assert(text_firstDifferentIndex(NP_TEXT(""), ' ') == 0,
		   "Returns `0` if string is empty.")
	assert(text_firstDifferentIndex(NP_TEXT("       "), ' ') == 7,
		   "Returns `7` if string is composed of only 7 undesired chars.")
		   
	return 0;
}
