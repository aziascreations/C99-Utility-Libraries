/** @file */

/** @defgroup group_nptext String utilities
 *
 *  Collection of various utility functions for `char` and `wchar_t` based strings.
 *
 *  @{
 */

#include "ctype.h"
#include "stdlib.h"
#include "string.h"

#include "text.h"

char *copyString(char *stringToCopy) {
	// FIXME: The malloc doesn't look right at all, check this !
	
	// Preparing the output buffer
	size_t stringByteSize = strlen(stringToCopy) + 1;
	char *newString = malloc(stringByteSize);
	
	// Copying and validating the operation's success
	if(newString) {
		// TODO: Restore when using C11 !
		//if(strcpy_s(newString, stringByteSize, stringToCopy)) {
		//	free(newString);
		//	newString = NULL;
		//}
		// Temporary safe fix for C11's strcpy_s in C99.
		memcpy(newString, stringToCopy, stringByteSize);
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
			// TODO: Benchmark this !
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

char *text_copyLine(const char *string, size_t stringLength, char **nextLine, size_t *nextLineMaxLength) {
	if(string == NULL || stringLength <= 0) {
		// Setting the return values to NULL/0 to prevent infinite loops.
		if(nextLine != NULL) {
			*nextLine = NULL;
		}
		if(nextLineMaxLength != NULL) {
			*nextLineMaxLength = 0;
		}
		return NULL;
	}
	
	// Going along the string until we find its end or a line return.
	size_t lineLength = 0;
	while(string[lineLength] != '\0' && string[lineLength] != '\r' && string[lineLength] != '\n' &&
		  lineLength < stringLength) {
		lineLength++;
	}
	
	// Attempting to find the start of the next line if required.
	if(nextLine != NULL) {
		size_t nextLineOffset = lineLength;
		
		// Point to NULL/no next string by default for safety reasons.
		*nextLine = NULL;
		
		// If we aren't right at the end of the string, we check for the presence of a CRLF or LFCR.
		if(nextLineOffset < stringLength) {
			
			if(string[nextLineOffset] == '\r') {
				if(string[nextLineOffset + 1] == '\n') {
					nextLineOffset++;
				}
				nextLineOffset++;
			} else if(string[nextLineOffset] == '\n') {
				if(string[nextLineOffset + 1] == '\r') {
					nextLineOffset++;
				}
				nextLineOffset++;
			} else if(string[nextLineOffset] == '\0') {
				// Edge case that shouldn't happen unless `stringLength` wrongfully includes a '\0'.
				// We'll simply say that there's nothing after this line to prevent issues.
				nextLineOffset = stringLength;
			}
		}
		
		if(stringLength - nextLineOffset > 0) {
			*nextLine = ((char *) string) + nextLineOffset;
		}
		
		// Preventing further expensive `strlen` calls when used in loops.
		if(nextLineMaxLength != NULL) {
			*nextLineMaxLength = stringLength - nextLineOffset;
		}
	}
	
	// Copying the line safely.
	char *copiedLine = calloc(lineLength + 1, sizeof(char));
	
	if(copiedLine != NULL) {
		memcpy(copiedLine, string, lineLength);
	}
	
	return copiedLine;
}

/** @} */ // end of group_nptext
