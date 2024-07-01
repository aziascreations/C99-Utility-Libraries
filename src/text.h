/** @file */

#if !defined(NP_ONCE_C99_GOODIES_TEXT)
#define NP_ONCE_C99_GOODIES_TEXT

#include "platform.h"

#include <stdbool.h>
#include <string.h>
#include <wchar.h>

#if defined(NP_GOODIES_EXPORT_TEXT) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_TEXT NP_DLL_EXPORT
#else
	#define DLL_EXP_TEXT
#endif

// Generic macros
#define text_areStringsEqualA(string1, string2) (strcmp(string1, string2) == 0)
#define text_areStringsEqualW(string1, string2) (wcscmp(string1, string2) == 0)

// Unicode macros
#if defined(NP_UNICODE)
#define text_areStringsEqual text_areStringsEqualW
#define text_copy text_copyW
#define text_copy_s text_copyW_s
#define text_startsWith text_startsWithW
#define text_isEmpty text_isEmptyW
#define text_nextSpaceIndex text_nextSpaceIndexW
#define text_firstDifferentIndex text_firstDifferentIndexW
#define text_lastDifferentIndex text_lastDifferentIndexW
#define text_trim text_trimW
#define text_copyLine text_copyLineW
#else
#define text_areStringsEqual text_areStringsEqualA
#define text_copy text_copyA
#define text_copy_s text_copyA_s
#define text_startsWith text_startsWithA
#define text_isEmpty text_isEmptyA
#define text_nextSpaceIndex text_nextSpaceIndexA
#define text_firstDifferentIndex text_firstDifferentIndexA
#define text_lastDifferentIndex text_lastDifferentIndexA
#define text_trim text_trimA
#define text_copyLine text_copyLineA
#endif

/**
 * Copies the given string into a new buffer and returns said buffer as-is.
 * @param string The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT char *text_copyA(const char *string);

/**
 * Copies the given string into a new buffer and returns said buffer as-is.
 * @param string The string to be copied.
 * @param maxLength The string's maximum character count, not including the trailing NULL byte.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT char *text_copyA_s(const char *string, size_t maxLength);

/**
 * Copies the given string into a new buffer and returns said buffer as-is.
 * @param string The string to be copied.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT wchar_t *text_copyW(const wchar_t *string);

/**
 * Copies the given string into a new buffer and returns said buffer as-is.
 * @param string The string to be copied.
 * @param maxLength The string's maximum character count.
 * @return The copied string's pointer, or `NULL` if an error occurred.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT wchar_t *text_copyW_s(const wchar_t *string, size_t maxLength);

/**
 * Checks if a given \a string starts with a given \a prefix.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
DLL_EXP_TEXT bool text_startsWithA(const char *string, const char *prefix);

/**
 * Checks if a given \a string starts with a given \a prefix.
 * @param string The searched string.
 * @param prefix The prefix to be searched for in \a string.
 * @return `true` if the string starts with the given prefix, `false` otherwise.
 */
DLL_EXP_TEXT bool text_startsWithW(const wchar_t *string, const wchar_t *prefix);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
DLL_EXP_TEXT bool text_isEmptyA(const char *string);

/**
 * Checks if the given \a string is `NULL`, empty or filled with spaces.
 * @param string The string to be checked.
 * @return `true` if the string is empty, `false` otherwise.
 */
DLL_EXP_TEXT bool text_isEmptyW(const wchar_t *string);

/**
 * Finds the next space in a given string and returns its index.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
DLL_EXP_TEXT int text_nextSpaceIndexA(const char *string, int startIndex);

/**
 * Finds the next space in a given string and returns its index.
 * @param string The string to be analysed.
 * @param startIndex The index at which the search will start in the given \a string.
 * @return The index at which the next space will be located if found, or the string's end index.
 */
DLL_EXP_TEXT int text_nextSpaceIndexW(const wchar_t *string, int startIndex);

/**
 * Finds the first non-excluded char in a string and returns its index.
 * @param string The analysed string.
 * @param excludedChar The character that should be skipped over.
 * @return The first non-excluded char's index, or `0` if the string or excluded char is NULL.
 */
DLL_EXP_TEXT size_t text_firstDifferentIndexA(const char *string, char excludedChar);

/**
 * Finds the first non-excluded char in a string and returns its index.
 * @param string The analysed string.
 * @param excludedChar The character that should be skipped over.
 * @return The first non-excluded char's index, or `0` if the string or excluded char is NULL.
 */
DLL_EXP_TEXT size_t text_firstDifferentIndexW(const wchar_t *string, wchar_t excludedChar);

/**
 * Finds the last non-excluded char in a string and returns its index.
 * @param string The analysed string.
 * @param excludedChar The character that should be skipped over.
 * @return The last non-excluded char's index.<br>
 *         If none were present, the return value will be the `strlen(string) - 1`.<br>
 *         If the string is empty or NULL, and if the excluded char is NULL, it will return `0`.
 * @warning The returned value points at the character BEFORE the last ignored one.<br>
 *          You should assume the next character is either ignored or a '\0'.
 */
DLL_EXP_TEXT size_t text_lastDifferentIndexW(const wchar_t *string, wchar_t excludedChar);

/**
 * Finds the last non-excluded char in a string and returns its index.
 * @param string The analysed string.
 * @param excludedChar The character that should be skipped over.
 * @return The last non-excluded char's index.<br>
 *         If none were present, the return value will be the `wcslen(string) - 1`.<br>
 *         If the string is empty or NULL, and if the excluded char is NULL, it will return `0`.
 * @warning The returned value points at the character BEFORE the last ignored one.<br>
 *          You should assume the next character is either ignored or a '\0'.
 */
DLL_EXP_TEXT size_t text_lastDifferentIndexA(const char *string, char excludedChar);

/**
 * Trims the given character from a string's left and right side.<br>
 * The returned string is a trimmed copy of the given string.
 * @param string The string that will be trimmed.
 * @param trimmedChar The character that should be trimmed.
 * @return The trimmed string as a new string.<br>
 *         Or `NULL` is the string or character were NULL, or if the resulting string would have been empty.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT char *text_trimA(const char *string, char trimmedChar);

/**
 * Trims the given character from a string's left and right side.<br>
 * The returned string is a trimmed copy of the given string.
 * @param string The string that will be trimmed.
 * @param trimmedChar The character that should be trimmed.
 * @return The trimmed string as a new string.<br>
 *         Or `NULL` is the string or character were NULL, or if the resulting string would have been empty.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT wchar_t *text_trimW(const wchar_t *string, wchar_t trimmedChar);

/**
 * Converts a given `char` string into a `wchar_t` one and returns its pointer.
 * @param originalString The original string to be copied
 * @return The converted string's pointer, or `NULL` if an error occurred.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_TEXT wchar_t *text_charToWChar(const char *originalString);

/**
 * Copies the first available line in the given string into a new buffer and returns said buffer as-is.<br>
 * Depending on the arguments given, it can also easily iterate over every line in a block of text.
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
DLL_EXP_TEXT char *text_copyLineA(
		const char *string,
		size_t stringLength,
		char **nextLine,
		size_t *nextLineMaxLength);

/**
 * Copies the first available line in the given string into a new buffer and returns said buffer as-is.<br>
 * Depending on the arguments given, it can also easily iterate over every line in a block of text.
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
DLL_EXP_TEXT wchar_t *text_copyLineW(
		const wchar_t *string,
		size_t stringLength,
		wchar_t **nextLine,
		size_t *nextLineMaxLength);

#endif /* !NP_ONCE_C99_GOODIES_TEXT */
