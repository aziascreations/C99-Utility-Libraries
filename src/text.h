/** @file */

#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(NP_GOODIES_EXPORT_TEXT) || defined(NP_GOODIES_EXPORT_ALL)
	#if WIN32 || defined(_MSC_VER)
		#define DLL_EXP_TEXT __declspec(dllexport)
	#elif UNIX || defined(__GNUC__)
		#define DLL_EXP_TEXT __attribute__((visibility("default")))
	#else
		#define DLL_EXP_TEXT
		#warning Unknown platform, prevent library exports !
	#endif
#else
	#define DLL_EXP_TEXT
#endif

#define areStringsEqual(string1, string2) (strcmp(string1, string2) == 0)
#define areWCharStringsEqual(string1, string2) (wcscmp(string1, string2) == 0)

/**
 * Copies the given string into a new buffer and returns said buffer as-is.<br>
 * Uses `strcpy_s` internally.
 * @param stringToCopy The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 */
DLL_EXP_TEXT char *copyString(char *stringToCopy);

/**
 * Checks if a given \a string starts with a given \a prefix.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
DLL_EXP_TEXT bool stringStartsWith(char *string, char *prefix);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
DLL_EXP_TEXT bool isStringEmpty(char *string);

/**
 * Finds the next space in a given string and returns its index.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
DLL_EXP_TEXT int nextCharSpaceIndex(const char *string, int startIndex);

#ifdef NP_WIN32
/**
 * Copies the given string into a new buffer and returns said buffer as-is.<br>
 * Uses `wcscpy_s` internally.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param stringToCopy The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 */
DLL_EXP_TEXT wchar_t *copyWCharString(wchar_t *stringToCopy);

/**
 * Checks if a given \a string starts with a given \a prefix.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
DLL_EXP_TEXT bool wCharStringStartsWith(wchar_t *string, wchar_t *prefix);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
DLL_EXP_TEXT bool isWCharStringEmpty(wchar_t *string);

/**
 * Converts a given `char` string into a `wchar_t` one and returns its pointer.<br>
 * You will need to free the returned pointer when appropriate.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param originalString The original string to be copied
 * @return The converted string's pointer, or `NULL` if an error occurred.
 */
DLL_EXP_TEXT wchar_t *charStringToWChar(char *originalString);

/**
 * Finds the next space in a given string and returns its index.<br>
 * Only available if `NP_WIN32` is defined during compilation.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
DLL_EXP_TEXT int nextWCharSpaceIndex(const wchar_t *string, int startIndex);

#endif


/**
 * Copies the first available line in the given string into a new buffer and returns said buffer as-is.<br>
 * ???
 * @param string The string whose first line will be copied and returned.
 * @param stringLength The given string's length with or without the trailing NULL byte.<br>
 *                     May overshoot the actual length if a NULL byte is present in the string.<br>
 *                     And may also undershoot the actual length to simulate a truncated string.
 * @param nextLine Optional pointer to a string pointer that is set to the start of the next line in the given text.
 *                 If no more line is present in the given text, it will be set to NULL.<br>
 *                 This pointer must never be freed !
 * @param nextLineMaxLength Optional pointer that returns expected remaining string length for `nextLine`.<br>
 *                          Will be ignored if `nextLine` is NULL.
 * @return The copied line's pointer, or `NULL` if an error occurred or no line could be found.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT char *text_copyLine(const char *string, size_t stringLength, char **nextLine, size_t *nextLineMaxLength);

#ifdef NP_WIN32
//DLL_EXP_TEXT wchar_t *text_copyLineW(const wchar_t *string, size_t stringLength, wchar_t **nextLine, size_t *nextLineMaxLength);
#endif
