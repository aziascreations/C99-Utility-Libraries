#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../assert.h"

#include "../../src/text.h"

// Test strings
static const char *text_01 = "Hello world !";

int main(void) {
	// Preliminary test
	assert(text_charToWChar(NULL) == NULL,
		   "Giving NULL returns NULL")
	
	// Converting the string
	wchar_t *convertedText = text_charToWChar(text_01);
	assert(convertedText != NULL,
		   "The returned string isn't NULL")
	
	// Basic tests
	assert(strlen(text_01) == wcslen(convertedText),
		   "The strings' length match")
	assert(wcscmp(convertedText, L"Hello world !") == 0,
		   "The converted string's content is what was expected")
	
	// Cleaning up
	free(convertedText);
	
	// Printing C11 optimizations warning
	#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
	assert_warn(true, "Tested on C11 variant, C99 wasn't tested !")
	#else
	assert_warn(true, "Tested on C99 variant, C11 wasn't tested !")
	#endif

	return 0;
}
