/** @file */

/** @defgroup group_nptext String utilities
 *
 *  Collection of various utility functions for `char` and `wchar_t` based strings.
 *
 *  @{
 */

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <wctype.h>

#include "text.h"

//#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
//#include <stdio.h>

char *text_copy(const char *string) {
	// Safety check
	if(string == NULL) {
		return NULL;
	}
	
	size_t maxLength = strlen(string);
	char *newString = malloc((maxLength + 1) * sizeof(char));
	
	if(newString != NULL) {
		memcpy(newString, string, maxLength * sizeof(char));
		newString[maxLength] = '\0';
	}
	
	return newString;
}

char *text_copy_s(const char *string, size_t maxLength) {
	if(string == NULL || maxLength <= 0) {
		return NULL;
	}
	
	// Using an `strnlen_s` alternative that doesn't have undefined behaviour in some specific cases.
	// See: https://en.cppreference.com/w/c/string/byte/strlen#:~:text=of%20str.-,The%20behavior%20is%20undefined,-if%20both%20str
	size_t stringLength = 0;
	while(stringLength < maxLength && string[stringLength] != '\0') {
		stringLength++;
	}
	maxLength = (stringLength < maxLength) ? (stringLength) : (maxLength);
	
	char *newString = malloc((maxLength + 1) * sizeof(char));
	
	if(newString != NULL) {
		memcpy(newString, string, maxLength * sizeof(char));
		newString[maxLength] = '\0';
	}
	
	return newString;
}

wchar_t *text_copyW(const wchar_t *string) {
	// Safety checks
	if(string == NULL) {
		return NULL;
	}
	
	size_t maxLength = wcslen(string);
	wchar_t *newString = malloc((maxLength + 1) * sizeof(wchar_t));
	
	if(newString != NULL) {
		//#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
		//if(wcscpy_s(newString, maxLength, string)) {
		//	free(newString);
		//	newString = NULL;
		//}
		//#else
		memcpy(newString, string, maxLength * sizeof(wchar_t));
		newString[maxLength] = '\0';
		//#endif
	}
	
	return newString;
}

wchar_t *text_copyW_s(const wchar_t *string, size_t maxLength) {
	// Safety checks
	if(string == NULL || maxLength <= 0) {
		return NULL;
	}

	#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
	// This variant of `strnlen_s` doesn't have undefined bahaviour.
	// See: https://en.cppreference.com/w/c/string/wide/wcslen
	maxLength = wcsnlen_s(string, maxLength);
	#else
	// Using the same method as in `text_copy_s`.
	size_t stringLength = 0;
	while(stringLength < maxLength && string[stringLength] != '\0') {
		stringLength++;
	}
	maxLength = (stringLength < maxLength) ? (stringLength) : (maxLength);
	#endif
	
	wchar_t *newString = malloc((maxLength + 1) * sizeof(wchar_t));
	
	// Copying and validating the operation's success
	if(newString != NULL) {
		//#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
		//if(wcscpy_s(newString, maxLength, string)) {
		//	free(newString);
		//	newString = NULL;
		//}
		//#else
		memcpy(newString, string, maxLength * sizeof(wchar_t));
		newString[maxLength] = '\0';
		//#endif
	}
	
	return newString;
}

bool text_startsWith(const char *string, const char *prefix) {
	if(string == NULL || prefix == NULL) {
		return false;
	}
	
	size_t prefixLength = strlen(prefix);
	
	if(prefixLength > strlen(string)) {
		return false;
	}
	
	return memcmp(string, prefix, prefixLength) == 0;
}

bool text_startsWithW(const wchar_t *string, const wchar_t *prefix) {
	if(string == NULL || prefix == NULL) {
		return false;
	}
	
	size_t prefixLength = wcslen(prefix);
	
	if(prefixLength > wcslen(string)) {
		return false;
	}
	
	return memcmp(string, prefix, prefixLength * sizeof(wchar_t)) == 0;
}

bool text_isEmpty(const char *string) {
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

bool text_isEmptyW(const wchar_t *string) {
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

int text_nextSpaceIndex(const char *string, int startIndex) {
	if(string == NULL) {
		return 0;
	}
	
	size_t maxIndex = strlen(string);
	if(startIndex > maxIndex) {
		startIndex = (int) maxIndex;
	}
	
	while(startIndex < maxIndex && string[startIndex] != '\0' && string[startIndex] != ' ') {
		startIndex++;
	}
	
	return startIndex;
}

int text_nextSpaceIndexW(const wchar_t *string, int startIndex) {
	if(string == NULL) {
		return 0;
	}
	
	size_t maxIndex = wcslen(string);
	if(startIndex > maxIndex) {
		startIndex = (int) maxIndex;
	}
	
	while(startIndex < maxIndex && string[startIndex] != L'\0' && string[startIndex] != L' ') {
		startIndex++;
	}
	
	return startIndex;
}

size_t text_internal_firstDifferentIndex(const char *string, char excludedChar, size_t stringLength) {
	if(string != NULL && excludedChar != '\0') {
		size_t returnedIndex = 0;
		
		// We assume the `stringLength` is 100% valid.
		// This avoids repeating a `strlen` by forcing the source to do it.
		while(returnedIndex < stringLength && string[returnedIndex] == excludedChar) {
			returnedIndex++;
		}
		
		return returnedIndex;
	}
	
	return 0;
}

size_t text_internal_firstDifferentIndexW(const wchar_t *string, wchar_t excludedChar, size_t stringLength) {
	if(string != NULL && excludedChar != '\0') {
		size_t returnedIndex = 0;
		
		// We assume the `stringLength` is 100% valid.
		// This avoids repeating a `wcslen` by forcing the source to do it.
		while(returnedIndex < stringLength && string[returnedIndex] == excludedChar) {
			returnedIndex++;
		}
		
		return returnedIndex;
	}
	
	return 0;
}

size_t text_firstDifferentIndex(const char *string, char excludedChar) {
	if(string != NULL) {
		return text_internal_firstDifferentIndex(string, excludedChar, strlen(string));
	} else {
		return 0;
	}
}

size_t text_firstDifferentIndexW(const wchar_t *string, wchar_t excludedChar) {
	if(string != NULL) {
		return text_internal_firstDifferentIndexW(string, excludedChar, wcslen(string));
	} else {
		return 0;
	}
}

//char *text_trim(const char *string, char trimmedChar) {
//	//if(string == NULL) {
//	//
//	//}
//}
//
//wchar_t *text_trimW(const wchar_t *string, wchar_t trimmedChar) {
//
//}

wchar_t *text_charToWChar(const char *originalString) {
	if(originalString == NULL) {
		return NULL;
	}
	
	size_t originalLength = strlen(originalString);
	wchar_t *returnedString = (wchar_t *) malloc(sizeof(wchar_t) * (originalLength + 1));
	
	#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
	size_t outSize;
	
	errno = mbstowcs_s(&outSize, returnedString, originalLength + 1, originalString, originalLength);
	
	if(errno != 0) {
		free(returnedString);
		returnedString = NULL;
	}
	#else
	size_t outSize = mbstowcs(returnedString, originalString, originalLength);
	returnedString[originalLength] = '\0';
	
	if(outSize == -1) {
		free(returnedString);
		returnedString = NULL;
	}
	#endif
	
	return returnedString;
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
			//*nextLine = ((char *) string) + (nextLineOffset * sizeof(char));
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
		memcpy(copiedLine, string, lineLength * sizeof(char));
	}
	
	return copiedLine;
}

wchar_t *text_copyLineW(const wchar_t *string, size_t stringLength, wchar_t **nextLine, size_t *nextLineMaxLength) {
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
			//*nextLine = ((wchar_t *) string) + (nextLineOffset * sizeof(wchar_t));
			*nextLine = ((wchar_t *) string) + nextLineOffset;
		}
		
		// Preventing further expensive `strlen` calls when used in loops.
		if(nextLineMaxLength != NULL) {
			*nextLineMaxLength = stringLength - nextLineOffset;
		}
	}
	
	// Copying the line safely.
	wchar_t *copiedLine = calloc(lineLength + 1, sizeof(wchar_t));
	
	if(copiedLine != NULL) {
		memcpy(copiedLine, string, lineLength * sizeof(wchar_t));
	}
	
	return copiedLine;
}

/** @} */ // end of group_nptext
