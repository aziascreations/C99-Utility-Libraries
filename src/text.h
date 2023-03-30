#pragma once

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define areStringsEqual(string1, string2) (strcmp(string1, string2) == 0)

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
bool stringStartsWith(char* string, char* prefix);

/**
 * Checks if a given <i>string</i> is empty or filled with spaces.
 * @param str
 * @return
 */
bool isStringEmpty(char *str);