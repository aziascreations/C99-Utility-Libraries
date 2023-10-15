/** @file */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../platform.h"

#include "./structs.h"

#if defined(NP_GOODIES_EXPORT_UUID) || defined(NP_GOODIES_EXPORT_UUID_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_UUID NP_DLL_EXPORT
#else
	#define DLL_EXP_UUID
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
DLL_EXP_UUID char *uuid_toString(struct uuid *uuid);

/**
 * abc todo
 */
#define uuid_compare(uuid_a, uuid_b) (memcmp(uuid_a, uuid_b, sizeof(struct uuid)))

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
DLL_EXP_UUID wchar_t *uuid_toWcharString(struct uuid *uuid);

#endif
