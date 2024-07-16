/** @file */

#if !defined(NP_ONCE_C99_GOODIES_UUID_COMMONS)
#define NP_ONCE_C99_GOODIES_UUID_COMMONS

#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <wchar.h>

#include "../platform.h"

#include "./structs.h"

#if defined(NP_GOODIES_EXPORT_UUID) || defined(NP_GOODIES_EXPORT_UUID_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_UUID NP_DLL_EXPORT
#else
	#define DLL_EXP_UUID
#endif

#define UUID_BYTE_LENGTH 16

#define UUID_CHAR_COUNT (32 + 4)


// Unicode macros
//#if defined(NP_UNICODE)
//	#define uuid_toString uuid_toStringW
//#else
//	#define uuid_toString uuid_toStringA
//#endif


/**
 * Generates a `char` string representation of a given UUID4.<br>
 *
 * The returned string should match the following regex:<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;`^[0-9A-F]{8}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{12}$`
 * @param uuid The UUID to represent as a string.
 * @return A `char *` string containing the representation of the given UUID.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_UUID char *uuid_toStringA(struct uuid *uuid);

/**
 * Compares the content of 2 UUID buffers.
 * @param uuid_a The first UUID to be compared.
 * @param uuid_b The second UUID to be compared.
 * @return `<0` if the content of `uuid_a` is less than the contents of `uuid_b`.<br>
 *         `0` if the content of `uuid_a` is the same as the contents of `uuid_b`.<br>
 *         `>0` if the content of `uuid_a` is bigger than the contents of `uuid_b`.
 */
#define uuid_compare(uuid_a, uuid_b) (memcmp(uuid_a, uuid_b, sizeof(struct uuid)))

/**
 * Generates a `wchar_t` string representation of a given UUID4.<br>
 *
 * The returned string should match the following regex:<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;`^[0-9A-F]{8}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{4}-[0-9A-F]{12}$`
 *
 * @param uuid The UUID to represent as a string.
 * @return A `wchar_t *` string containing the representation of the given UUID.
 * @warning Failure to free the returned string WILL cause memory leaks !
 */
DLL_EXP_UUID wchar_t *uuid_toStringW(struct uuid *uuid);

#endif /* !NP_ONCE_C99_GOODIES_UUID_COMMONS */
