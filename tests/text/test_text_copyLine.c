#include <stdio.h>

#include "../assert.h"
#include "../memutils.h"

#include "../../src/debug.h"
#include "../../src/text.h"

// Test strings
static const char *text_01 = "Regular simple line";
static const char *text_02 = "";

static const char *text_10 = "CR end\r";
static const char *text_11 = "LF end\n";
static const char *text_12 = "CRLF end\r\n";
static const char *text_13 = "LFCR end\n\r";
static const char *text_14 = "NULL end\0\0";  // Adding 2 '\0' to be sure extra sure we have more than 1.

static const char *text_20 = "Line 1\rLine 2\rLine 3";
static const char *text_21 = "Line 1\nLine 2\nLine 3";
static const char *text_22 = "Line 1\r\nLine 2\r\nLine 3";
static const char *text_23 = "Line 1\n\rLine 2\n\rLine 3";

static const char *text_30 = "Line 1\r\rLine 3";
static const char *text_31 = "Line 1\n\nLine 3";
static const char *text_32 = "Line 1\r\n\r\nLine 3";
static const char *text_33 = "Line 1\n\r\n\rLine 3";

static const char *text_40 = "Line 1\rLine 2\0Line 3";

int main(void) {
	// Preparing temporary variables.
	char *tmpLine = NULL;
	char *tmpNextLine = NULL;
	size_t tmpNextLength = 0;
	
	// FIXME: Make 200% sure we don't overrun the buffer if it ends with \r instead of \0 and doesn't include one !.
	
	// Testing text 01
	{
		assert(strlen(text_01) == 19, "Text 01: Length is `19` chars.")
		
		tmpLine = text_copyLine(text_01, strlen(text_01), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 01: Copied line isn't NULL.")
		assert(strcmp(text_01, tmpLine) == 0, "Text 01: Copied line is the same as the original.")
		assert(text_01 != tmpLine, "Text 01: Copied line doesn't point to the original.")
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 20, "Text 01: Copied line's memory size is `20` chars long.")
		assert(strlen(tmpLine) == 19, "Text 01: Copied line's strlen is `19` chars long.")
		
		assert(tmpNextLine == NULL, "Text 01: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 01: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 01 - Undersized
	{
		tmpLine = text_copyLine(text_01, strlen(text_01) - 5, &tmpNextLine, &tmpNextLength);
		
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 15, "Text 01 - Undersized: Copied line's memory size is `15` chars long.")
		assert(strlen(tmpLine) == 14, "Text 01 - Undersized: Copied line's strlen is `14` chars long.")
		assert(tmpNextLine == NULL, "Text 01 - Undersized: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 01 - Undersized: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 02
	{
		assert(strlen(text_02) == 0, "Text 02: Length is `0` char.")
		
		tmpLine = text_copyLine(text_02, strlen(text_02), &tmpNextLine, &tmpNextLength);
		assert(tmpLine == NULL, "Text 02: Copied line is NULL.")
		assert(tmpNextLine == NULL, "Text 02: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 02: Has zero characters left.")
		
		// Forcing the function to think we have an empty string with more content after.
		// This is normal and caused by us going further than the '\0'.
		// However, the function will see the '\0' right away and indicate to us that the line it expected
		//  is empty and has nothing after it and its non-existent non-'\0' line ending.
		// Another way to see it is that we "trick" it into believing we gave it "\r\0".
		// This is an edge-case TBH, and it shouldn't happen unless voluntarily provoked.
		tmpLine = text_copyLine(text_02, strlen(text_02) + 42, &tmpNextLine, &tmpNextLength);
		assert(tmpLine != NULL, "Text 02: Copied line isn't NULL anymore, its length was faked.")
		assert(strlen(tmpLine) == 0, "Text 02: Copied line's strlen is `0` chars long.")
		assert(tmpNextLine == NULL, "Text 02: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 02: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 10-13
	{
		assert(strlen(text_10) == 7, "Text 10: Length is `7` char.")
		assert(strlen(text_11) == 7, "Text 11: Length is `7` char.")
		assert(strlen(text_12) == 10, "Text 12: Length is `10` char.")
		assert(strlen(text_13) == 10, "Text 13: Length is `10` char.")
		
		tmpLine = text_copyLine(text_10, strlen(text_10), &tmpNextLine, &tmpNextLength);
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 7, "Text 10: Copied line's memory size is `7` chars long.")
		assert(strlen(tmpLine) == 6, "Text 10: Copied line's strlen is `6` chars long.")
		assert(tmpNextLine == NULL, "Text 10: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 10: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_11, strlen(text_11), &tmpNextLine, &tmpNextLength);
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 7, "Text 11: Copied line's memory size is `7` chars long.")
		assert(strlen(tmpLine) == 6, "Text 11: Copied line's strlen is `6` chars long.")
		assert(tmpNextLine == NULL, "Text 11: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 11: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_12, strlen(text_12), &tmpNextLine, &tmpNextLength);
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 9, "Text 12: Copied line's memory size is `9` chars long.")
		assert(strlen(tmpLine) == 8, "Text 12: Copied line's strlen is `8` chars long.")
		assert(tmpNextLine == NULL, "Text 12: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 12: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_13, strlen(text_13), &tmpNextLine, &tmpNextLength);
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 9, "Text 13: Copied line's memory size is `9` chars long.")
		assert(strlen(tmpLine) == 8, "Text 13: Copied line's strlen is `8` chars long.")
		assert(tmpNextLine == NULL, "Text 13: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 13: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 14
	{
		assert(strlen(text_14) == 8, "Text 14: Length is `8` chars.")
		
		tmpLine = text_copyLine(text_14, strlen(text_14) + 2, &tmpNextLine, &tmpNextLength);
		
		assert(memUtils_getSize(tmpLine) == sizeof(char) * 9, "Text 14: Copied line's memory size is `9` chars long.")
		assert(strlen(tmpLine) == 8, "Text 14: Copied line's strlen is `8` chars long.")
		
		assert(tmpNextLine == NULL, "Text 14: Has no 2nd line. (Ended with a '\\0')")
		assert(tmpNextLength == 0, "Text 14: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	return 0;
}