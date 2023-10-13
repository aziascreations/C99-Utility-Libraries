/** @file */

#pragma once

#include <stdlib.h>

#include "./uuid.h"
#include "./structs.h"

#if defined(NP_GOODIES_EXPORT_UUID4) || defined(NP_GOODIES_EXPORT_UUID_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#if WIN32 || defined(_MSC_VER)
		#define DLL_EXP_UUID4 __declspec(dllexport)
	#elif UNIX || defined(__GNUC__)
		#define DLL_EXP_UUID4 __attribute__((visibility("default")))
	#else
		#define DLL_EXP_UUID4
		#warning Unknown platform, prevent library exports !
	#endif
#else
	#define DLL_EXP_UUID4
#endif

/**
 * Generate a new \ref uuid "UUID4" and returns its pointer.
 * @return The \ref uuid "UUID4"'s pointer, or `NULL` if an error occurred.
 */
DLL_EXP_UUID4 UUID4 *uuid4_generate();
