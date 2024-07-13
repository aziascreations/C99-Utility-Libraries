/** @file */

#if !defined(NP_ONCE_C99_GOODIES_UUID_UUID4)
#define NP_ONCE_C99_GOODIES_UUID_UUID4

#include <stdbool.h>
#include <stdlib.h>

#include "../platform.h"

#include "./uuid.h"
#include "./structs.h"

#if defined(NP_GOODIES_EXPORT_UUID4) || defined(NP_GOODIES_EXPORT_UUID_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_UUID4 NP_DLL_EXPORT
#else
	#define DLL_EXP_UUID4
#endif

/**
 * Generate a new \ref uuid "UUID4" and returns its pointer.
 * @param cb_randomFillBuffer Callback used to fill the UUID4's buffer with random data.<br>
 *                            If it returns `true` the RNG succeeded, if `false`, the `uuid4_generate` function will
 *                            return NULL.
 * @return The \ref uuid "UUID4"'s pointer, or `NULL` if an error occurred.
 */
DLL_EXP_UUID4 UUID4 *uuid4_generate(bool (*cb_randomFillBuffer)(void *buffer, size_t length));

#endif /* !NP_ONCE_C99_GOODIES_UUID_UUID4 */
