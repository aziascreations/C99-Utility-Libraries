#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define areStringsEqual(string1, string2) (strcmp(string1, string2) == 0)
#define areWCharStringsEqual(string1, string2) (wcscmp(string1, string2) == 0)

/**
 * Copies the given string into a new buffer and returns it as-is.
 * Uses <code>strcpy_s</code> internally.
 * @param stringToCopy The string to be copied
 * @return The copied string, on <code>NULL</code> if an error occurred.
 */
char *copyString(char *stringToCopy);

/**
 * Checks if a given <i>string</i> starts with a given <i>prefix</i>.
 * @param string
 * @param prefix
 * @return
 */
bool stringStartsWith(char *string, char *prefix);

/**
 * Checks if a given <i>string</i> is empty or filled with spaces.
 * @param string
 * @return
 */
bool isStringEmpty(char *string);

/**
 * Finds the next space in a given string and returns its index.
 * @param string
 * @param startIndex
 * @return
 */
int nextCharSpaceIndex(const char *string, int startIndex);

#ifdef NP_WIN32
/**
 * Copies the given string into a new buffer and returns it as-is.
 * Uses <code>???</code> internally.
 * @param stringToCopy The string to be copied
 * @return The copied string, on <code>NULL</code> if an error occurred.
 */
wchar_t *copyWCharString(wchar_t *stringToCopy);

/**
 * Checks if a given <i>string</i> starts with a given <i>prefix</i>.
 * @param string
 * @param prefix
 * @return
 */
bool wCharStringStartsWith(wchar_t *string, wchar_t *prefix);

/**
 * Checks if a given <i>string</i> is empty or filled with spaces.
 * @param string
 * @return
 */
bool isWCharStringEmpty(wchar_t *string);

/**
 * Converts a given `char` string into a `wchar_t` one.
 * You will need to free the returned pointer once appropriate.
 * @param originalString The original string to be copied
 * @return The converted string's pointer, or `NULL` if an error occurred.
 */
wchar_t *charStringToWChar(char *originalString);

/**
 * Finds the next space in a given string and returns its index.
 * @param string
 * @param startIndex
 * @return
 */
int nextWCharSpaceIndex(const wchar_t *string, int startIndex);

#endif
