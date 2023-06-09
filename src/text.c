/// @file text.c

/** @defgroup group_nptext String utilities
 *
 *  Collection of various utility functions for `char` and `wchar_t` based strings.
 *
 *  <b>Warning:</b><br>
 *  Unless `NP_WIN32` is defined, all functions that uses or return a `wchar_t` typed variable won't be accessible.<br>
 *  This is due to the fact that `wchar_t` is only accessible easily on Windows platforms.
 *
 *  @{
 */
 
#include "text.h"

char *copyString(char *stringToCopy) {
	// Preparing the output buffer
	size_t stringByteSize = strlen(stringToCopy) + 1;
	char *newString = malloc(stringByteSize);
	
	// Copying and validating the operation's success
	if(newString) {
		if(strcpy_s(newString, stringByteSize, stringToCopy)) {
			free(newString);
			newString = NULL;
		}
	}
	
	return newString;
}

bool stringStartsWith(char *string, char *prefix) {
	size_t prefixLength = strlen(prefix);
	
	if(prefixLength > strlen(string)) {
		return false;
	}
	
	return memcmp(string, prefix, prefixLength) == 0;
}

bool isStringEmpty(char *string) {
	if(string != NULL) {
		size_t len = strlen(string);
		
		for(int i = 0; i < len; i++) {
			if(!isspace(string[i])) {
				return false;
			}
		}
	}
	
	return true;
}

int nextCharSpaceIndex(const char *string, int startIndex) {
	while(string[startIndex] != '\0' && string[startIndex] != ' ') {
		startIndex++;
	}
	return startIndex;
}

#ifdef NP_WIN32

wchar_t *copyWCharString(wchar_t *stringToCopy) {
	// Preparing the output buffer
	size_t stringSize = wcslen(stringToCopy) + 1;
	wchar_t *newString = malloc(stringSize * sizeof(wchar_t));
	
	// Copying and validating the operation's success
	if(newString) {
		if(wcscpy_s(newString, stringSize, stringToCopy)) {
			free(newString);
			newString = NULL;
		}
	}
	
	return newString;
}

bool wCharStringStartsWith(wchar_t *string, wchar_t *prefix) {
	size_t prefixLength = wcslen(prefix);
	
	if(prefixLength > wcslen(string)) {
		return false;
	}
	
	return memcmp(string, prefix, prefixLength * sizeof(wchar_t)) == 0;
}

bool isWCharStringEmpty(wchar_t *string) {
	if(string != NULL) {
		size_t len = wcslen(string);
		
		for(int i = 0; i < len; i++) {
			if(!iswspace(string[i])) {
				return false;
			}
		}
	}
	
	return true;
}

wchar_t *charStringToWChar(char *originalString) {
	size_t originalLength = strlen(originalString) + 1;
	wchar_t *returnedString = (wchar_t *) malloc(sizeof(wchar_t) * originalLength);
	size_t outSize;
	
	errno = mbstowcs_s(&outSize, returnedString, originalLength, originalString, originalLength - 1);
	
	if(errno != 0) {
		free(returnedString);
		returnedString = NULL;
	}
	
	return returnedString;
}

int nextWCharSpaceIndex(const wchar_t *string, int startIndex) {
	while(string[startIndex] != L'\0' && string[startIndex] != L' ') {
		startIndex++;
	}
	return startIndex;
}

#endif

/** @} */ // end of group_nptext
