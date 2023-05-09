/** @file */

#pragma once

#include <stdlib.h>

#include "./uuid.h"
#include "./structs.h"

#ifdef NP_UUID4_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 * Generate a new \ref uuid "UUID4" and returns its pointer.
 * @return The \ref uuid "UUID4"'s pointer, or `NULL` if an error occurred.
 */
DLL_EXPORT UUID4 *uuid4_generate();
