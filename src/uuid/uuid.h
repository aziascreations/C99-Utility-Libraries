/** @file */

#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "./structs.h"

#ifdef NP_UUID4_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#define UUID_BYTE_LENGTH 16

#define UUID_CHAR_COUNT (32 + 4)

/**
 * Generates a `char` string representation of a given UUID4.<br>
 *
 * The returned string should match the following regex:<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;`^[0-9A-F]{8}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{12}$`
 * @param uuid The UUID to represent as a string.
 * @return A `char *` string containing the representation of the given UUID.
 */
DLL_EXPORT char *uuid_toString(struct uuid *uuid);

#ifdef NP_WIN32

/**
 * Generates a `wchar_t` string representation of a given UUID4.<br>
 *
 * The returned string should match the following regex:<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;`^[0-9A-F]{8}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{12}$`
 *
 * Only available if `NP_WIN32` is defined during compilation.
 * @param uuid The UUID to represent as a string.
 * @return A `wchar_t *` string containing the representation of the given UUID.
 */
DLL_EXPORT wchar_t *uuid_toWcharString(struct uuid *uuid);

#endif
