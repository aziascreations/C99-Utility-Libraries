#include <stdio.h>

#include "../assert.h"

#include "../../src/text.h"

int main(void) {
	// Preliminary tests
	assert(text_lastDifferentIndex(NULL, ' ') == 0,
		   "Returns `0` if `string` is NULL and char is ' '")
	assert(text_lastDifferentIndex(NP_TEXT(" Hello :) "), '\0') == 0,
		   "Returns `0` if `string` isn't NULL and char is '\\0'")
	
	// Space-only tests
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !"), ' ') == 12,
		   "Returns `12` if string doesn't have the undesired char at its end.")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world ! "), ' ') == 12,
		   "Returns `12` if string has `1` undesired char at its end.")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world ! +  "), ' ') == 14,
		   "Returns `14` if string has `4` undesired char with the 4th separated its end.")
	
	// Symbols
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !"), '_') == 12,
		   "Returns `12` if string doesn't have the undesired char at its end. (Using symbols)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !   "), '_') == 15,
		   "Returns `15` if string doesn't have the undesired char at its end. (Using symbols)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !_"), '_') == 12,
		   "Returns `12` if string has `1` undesired char at its end. (Using symbols)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !_+___"), '_') == 14,
		   "Returns `14` if string has `4` undesired char with the 4th separated its end. (Using symbols)")
	
	// Special characters
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !"), '\t') == 12,
		   "Returns `12` if string doesn't have the undesired char at its end. (Using \\t)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !   "), '\t') == 15,
		   "Returns `15` if string doesn't have the undesired char at its end. (Using \\t)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !\t"), '\t') == 12,
		   "Returns `12` if string has `1` undesired char at its end. (Using \\t)")
	assert(text_lastDifferentIndex(NP_TEXT("Hello world !\t \t\t\t"), '\t') == 14,
		   "Returns `14` if string has `4` undesired char with the 4th separated its end. (Using \\t)")
		   
	// Edge-cases
	assert(text_lastDifferentIndex(NP_TEXT(""), ' ') == 0,
		   "Returns `0` if string is empty.")
	assert(text_lastDifferentIndex(NP_TEXT("       "), ' ') == 0,
		   "Returns `0` if string is composed of only 7 undesired chars.")
		   
	return 0;
}
