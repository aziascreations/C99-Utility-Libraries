/** @file */

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
 * @param stringToCopy The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 */
char *copyString(char *stringToCopy);

/**
 * Checks if a given \a string starts with a given \a prefix.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
bool stringStartsWith(char *string, char *prefix);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
bool isStringEmpty(char *string);

/**
 * Finds the next space in a given string and returns its index.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
int nextCharSpaceIndex(const char *string, int startIndex);

#ifdef NP_WIN32
/**
 * Copies the given string into a new buffer and returns said buffer as-is.<br>
 * Uses `wcscpy_s` internally.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param stringToCopy The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 */
wchar_t *copyWCharString(wchar_t *stringToCopy);

/**
 * Checks if a given \a string starts with a given \a prefix.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
bool wCharStringStartsWith(wchar_t *string, wchar_t *prefix);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
bool isWCharStringEmpty(wchar_t *string);

/**
 * Converts a given `char` string into a `wchar_t` one and returns its pointer.<br>
 * You will need to free the returned pointer when appropriate.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param originalString The original string to be copied
 * @return The converted string's pointer, or `NULL` if an error occurred.
 */
wchar_t *charStringToWChar(char *originalString);

/**
 * Finds the next space in a given string and returns its index.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
int nextWCharSpaceIndex(const wchar_t *string, int startIndex);

#endif
