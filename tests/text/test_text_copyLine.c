#include <stdio.h>
#include <stdlib.h>

#include "../../src/platform.h"

#include "../assert.h"
#include "../memutils.h"

#include "../../src/text.h"

// Test strings
static const text_char *text_01 = TEXT("Regular simple line");
static const text_char *text_02 = TEXT("");

static const text_char *text_10 = TEXT("CR end\r");
static const text_char *text_11 = TEXT("LF end\n");
static const text_char *text_12 = TEXT("CRLF end\r\n");
static const text_char *text_13 = TEXT("LFCR end\n\r");
static const text_char *text_14 = TEXT("NULL end\0\0");  // Adding 2 '\0' to be sure extra sure we have more than 1.

static const text_char *text_20 = TEXT("Line 1\rLine 2\rLine 3");
static const text_char *text_21 = TEXT("Line 1\nLine 2\nLine 3");
static const text_char *text_22 = TEXT("Line 1\r\nLine 2\r\nLine 3");
static const text_char *text_23 = TEXT("Line 1\n\rLine 2\n\rLine 3");

static const text_char *text_30 = TEXT("Line 1\r\rLine 3");
static const text_char *text_31 = TEXT("Line 1\n\nLine 3");
static const text_char *text_32 = TEXT("Line 1\r\n\r\nLine 3");
static const text_char *text_33 = TEXT("Line 1\n\r\n\rLine 3");

static const text_char *text_40 = TEXT("Line 1\rLine 2\0Line 3");

int main(void) {
	// Preliminary tests
	assert(text_copyLine(NULL, 42, NULL, NULL) == NULL,
		   "Returns NULL if `string` is NULL and length is positive")
		   
	// Preparing temporary variables.
	text_char *tmpLine = NULL;
	text_char *tmpNextLine = NULL;
	size_t tmpNextLength = 0;
	
	// FIXME: Make 200% sure we don't overrun the buffer if it ends with \r instead of \0 and doesn't include one !.
	
	// Testing text 01
	{
		assert(text_strlen(text_01) == 19, "Text 01: Length is `19` chars.")
		
		tmpLine = text_copyLine(text_01, text_strlen(text_01), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 01: Copied line isn't NULL.")
		assert(text_strcmp(text_01, tmpLine) == 0, "Text 01: Copied line is the same as the original.")
		assert(text_01 != tmpLine, "Text 01: Copied line doesn't point to the original.")

        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 20, "Text 01: Copied line's memory size is `>=20` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 20, "Text 01: Copied line's memory size is `==20` chars long.")
        #endif

		assert(text_strlen(tmpLine) == 19, "Text 01: Copied line's strlen is `19` chars long.")
		
		assert(tmpNextLine == NULL, "Text 01: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 01: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 01 - Undersized
	{
		tmpLine = text_copyLine(text_01, text_strlen(text_01) - 5, &tmpNextLine, &tmpNextLength);

        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 15, "Text 01 - Undersized: Copied line's memory size is `>=15` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 15, "Text 01 - Undersized: Copied line's memory size is `==15` chars long.")
        #endif

        assert(text_strlen(tmpLine) == 14, "Text 01 - Undersized: Copied line's strlen is `14` chars long.")
		assert(tmpNextLine == NULL, "Text 01 - Undersized: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 01 - Undersized: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 02
	{
		assert(text_strlen(text_02) == 0, "Text 02: Length is `0` char.")
		
		tmpLine = text_copyLine(text_02, text_strlen(text_02), &tmpNextLine, &tmpNextLength);
		assert(tmpLine == NULL, "Text 02: Copied line is NULL.")
		assert(tmpNextLine == NULL, "Text 02: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 02: Has zero characters left.")
		
		// Forcing the function to think we have an empty string with more content after.
		// This is normal and caused by us going further than the '\0'.
		// However, the function will see the '\0' right away and indicate to us that the line it expected
		//  is empty and has nothing after it and its non-existent non-'\0' line ending.
		// Another way to see it is that we "trick" it into believing we gave it "\r\0".
		// This is an edge-case TBH, and it shouldn't happen unless voluntarily provoked.
		tmpLine = text_copyLine(text_02, text_strlen(text_02) + 42, &tmpNextLine, &tmpNextLength);
		assert(tmpLine != NULL, "Text 02: Copied line isn't NULL anymore, its length was faked.")
		assert(text_strlen(tmpLine) == 0, "Text 02: Copied line's strlen is `0` chars long.")
		assert(tmpNextLine == NULL, "Text 02: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 02: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 10-13
	{
		assert(text_strlen(text_10) == 7, "Text 10: Length is `7` char.")
		assert(text_strlen(text_11) == 7, "Text 11: Length is `7` char.")
		assert(text_strlen(text_12) == 10, "Text 12: Length is `10` char.")
		assert(text_strlen(text_13) == 10, "Text 13: Length is `10` char.")
		
		tmpLine = text_copyLine(text_10, text_strlen(text_10), &tmpNextLine, &tmpNextLength);
        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 7, "Text 10: Copied line's memory size is `>=7` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 7, "Text 10: Copied line's memory size is `==7` chars long.")
        #endif
        assert(text_strlen(tmpLine) == 6, "Text 10: Copied line's strlen is `6` chars long.")
		assert(tmpNextLine == NULL, "Text 10: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 10: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_11, text_strlen(text_11), &tmpNextLine, &tmpNextLength);
        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 7, "Text 11: Copied line's memory size is `>=7` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 7, "Text 11: Copied line's memory size is `==7` chars long.")
        #endif
        assert(text_strlen(tmpLine) == 6, "Text 11: Copied line's strlen is `6` chars long.")
		assert(tmpNextLine == NULL, "Text 11: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 11: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_12, text_strlen(text_12), &tmpNextLine, &tmpNextLength);
		#ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 9, "Text 12: Copied line's memory size is `>=9` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 9, "Text 12: Copied line's memory size is `==9` chars long.")
        #endif
		assert(text_strlen(tmpLine) == 8, "Text 12: Copied line's strlen is `8` chars long.")
		assert(tmpNextLine == NULL, "Text 12: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 12: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
		
		tmpLine = text_copyLine(text_13, text_strlen(text_13), &tmpNextLine, &tmpNextLength);
        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 9, "Text 13: Copied line's memory size is `>=9` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 9, "Text 13: Copied line's memory size is `==9` chars long.")
        #endif
        assert(text_strlen(tmpLine) == 8, "Text 13: Copied line's strlen is `8` chars long.")
		assert(tmpNextLine == NULL, "Text 13: Has no 2nd line.")
		assert(tmpNextLength == 0, "Text 13: Has zero characters left.")
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 14
	{
		assert(text_strlen(text_14) == 8, "Text 14: Length is `8` chars.")
		
		tmpLine = text_copyLine(text_14, text_strlen(text_14) + 2, &tmpNextLine, &tmpNextLength);

        #ifndef NP_OS_WINDOWS
        assert(memUtils_getSize(tmpLine) >= sizeof(text_char) * 9, "Text 14: Copied line's memory size is `>=9` chars long.")
        #else
        assert(memUtils_getSize(tmpLine) == sizeof(text_char) * 9, "Text 14: Copied line's memory size is `==9` chars long.")
        #endif
        assert(text_strlen(tmpLine) == 8, "Text 14: Copied line's strlen is `8` chars long.")
		
		assert(tmpNextLine == NULL, "Text 14: Has no 2nd line. (Ended with a '\\0')")
		assert(tmpNextLength == 0, "Text 14: Has zero characters left.")
		
		free(tmpLine);
		tmpLine = NULL;
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 20
	{
		assert(text_strlen(text_20) == 20, "Text 20: Length is `20` chars.")
		
		tmpLine = text_copyLine(text_20, text_strlen(text_20), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 20: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 20: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 20: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 20: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 20: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 20: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 2")) == 0, "Text 20: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 20: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 20: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 20: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 20: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 20: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 21
	{
		assert(text_strlen(text_21) == 20, "Text 21: Length is `20` chars.")
		
		tmpLine = text_copyLine(text_21, text_strlen(text_21), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 21: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 21: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 21: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 21: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 21: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 21: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 2")) == 0, "Text 21: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 21: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 21: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 21: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 21: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 21: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 22
	{
		assert(text_strlen(text_22) == 22, "Text 22: Length is `22` chars.")
		
		tmpLine = text_copyLine(text_22, text_strlen(text_22), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 22: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 22: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 22: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 22: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 22: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 22: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 2")) == 0, "Text 22: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 22: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 22: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 22: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 22: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 22: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 23
	{
		assert(text_strlen(text_23) == 22, "Text 23: Length is `22` chars.")
		
		tmpLine = text_copyLine(text_23, text_strlen(text_23), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 23: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 23: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 23: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 23: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 23: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 23: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 2")) == 0, "Text 23: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 23: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 23: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 23: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 23: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 23: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 30
	{
		assert(text_strlen(text_30) == 14, "Text 30: Length is `14` chars.")
		
		tmpLine = text_copyLine(text_30, text_strlen(text_30), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 30: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 30: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 30: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 30: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 30: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 0, "Text 30: Copied line's length is `0` chars.")
		assert(text_strcmp(tmpLine, TEXT("")) == 0, "Text 30: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 30: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 30: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 30: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 30: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 30: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 31
	{
		assert(text_strlen(text_31) == 14, "Text 31: Length is `14` chars.")
		
		tmpLine = text_copyLine(text_31, text_strlen(text_31), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 31: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 31: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 31: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 31: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 31: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 0, "Text 31: Copied line's length is `0` chars.")
		assert(text_strcmp(tmpLine, TEXT("")) == 0, "Text 31: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 31: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 31: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 31: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 31: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 31: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 32
	{
		assert(text_strlen(text_32) == 16, "Text 32: Length is `16` chars.")
		
		tmpLine = text_copyLine(text_32, text_strlen(text_32), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 32: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 32: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 32: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 32: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 32: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 0, "Text 32: Copied line's length is `0` chars.")
		assert(text_strcmp(tmpLine, TEXT("")) == 0, "Text 32: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 32: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 32: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 32: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 32: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 32: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	// Testing text 33
	{
		assert(text_strlen(text_33) == 16, "Text 33: Length is `16` chars.")
		
		tmpLine = text_copyLine(text_33, text_strlen(text_33), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 33: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 33: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 33: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 33: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 33: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 0, "Text 33: Copied line's length is `0` chars.")
		assert(text_strcmp(tmpLine, TEXT("")) == 0, "Text 33: Copied line #2 only contains line #2.")
		assert(tmpNextLine != NULL, "Text 33: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 33: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 33: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 3")) == 0, "Text 33: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 33: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	//static const char *text_40 = "Line 1\rLine 2\0Line 3";
	// Testing text 40
	{
		assert(text_strlen(text_40) == 13, "Text 40: Length is `13` chars.")
		
		tmpLine = text_copyLine(text_40, text_strlen(text_40), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 40: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 40: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 1")) == 0, "Text 40: Copied line #1 only contains line #1.")
		assert(tmpNextLine != NULL, "Text 40: Next line isn't NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpLine = text_copyLine(tmpNextLine, text_strlen(tmpNextLine), &tmpNextLine, &tmpNextLength);
		
		assert(tmpLine != NULL, "Text 40: Copied line isn't NULL.")
		assert(text_strlen(tmpLine) == 6, "Text 40: Copied line's length is `6` chars.")
		assert(text_strcmp(tmpLine, TEXT("Line 2")) == 0, "Text 40: Copied line #2 only contains line #2.")
		assert(tmpNextLine == NULL, "Text 40: Next line is NULL.")
		
		free(tmpLine);
		tmpLine = NULL;
		
		tmpNextLine = NULL;
		tmpNextLength = 0;
	}
	
	return 0;
}
