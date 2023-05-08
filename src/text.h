#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define areStringsEqual(string1, string2) (strcmp(string1, string2) == 0)
#define areWCharStringsEqual(string1, string2) (wcscmp(string1, string2) == 0)

/**
 * Copies the given string into a new buffer and returns said buffer as-is.<br>
 * Uses `strcpy_s` internally.
 * @param stringToCopy The string to be copied
 * @return The copied string, on `NULL` if an error occurred.
 */
char *copyString(char *stringToCopy);

/**
 * Checks if a given <i>string</i> starts with a given <i>prefix</i>.
 * @param string
 * @param prefix
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
bool stringStartsWith(char *string, char *prefix);

/**
 * Checks if a given <i>string</i> is empty or filled with spaces.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
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
 * Copies the given string into a new buffer and returns it as-is.<br>
 * Uses `???` internally.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param stringToCopy The string to be copied
 * @return The copied string, on `NULL` if an error occurred.
 */
wchar_t *copyWCharString(wchar_t *stringToCopy);

/**
 * Checks if a given <i>string</i> starts with a given <i>prefix</i>.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string
 * @param prefix
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
bool wCharStringStartsWith(wchar_t *string, wchar_t *prefix);

/**
 * Checks if a given <i>string</i> is empty or filled with spaces.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
bool isWCharStringEmpty(wchar_t *string);

/**
 * Converts a given `char` string into a `wchar_t` one.<br>
 * You will need to free the returned pointer once appropriate.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param originalString The original string to be copied
 * @return The converted string's pointer, or `NULL` if an error occurred.
 */
wchar_t *charStringToWChar(char *originalString);

/**
 * Finds the next space in a given string and returns its index.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string
 * @param startIndex
 * @return
 */
int nextWCharSpaceIndex(const wchar_t *string, int startIndex);

#endif
