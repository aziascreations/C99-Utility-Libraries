/** @file */

#pragma once

#include <stdint.h>

#if defined(NP_GOODIES_EXPORT_CRC32) || defined(NP_GOODIES_EXPORT_HASH) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXP_CRC32 __declspec(dllexport)
#else
#define DLL_EXP_CRC32
#endif

/** @defgroup group_crc32 CRC32
 *
 *  This module contains small functions to calculate CRC32 hashes.
 *
 *  The currently supported variants are:<br>
 *  ● <b>CRC32B</b>&nbsp;&nbsp;&nbsp;&nbsp;<i>Common variant (7-Zip, ...)</i>
 *
 *  The future variants that are planned:<br>
 *  ● <b>CRC32C</b>&nbsp;&nbsp;&nbsp;&nbsp;<i>Intel intrinsic variant</i>
 *
 *  These functions were implemented to serve as a primitive hashmap hashing algorithm due
 *   to their relatively even distribution when cropping the hash of random data.<br>
 *  Some examples for this behaviour are present in the `extra/` directory.
 *
 *  Requires either `NP_GOODIES_EXPORT_CRC32`, `NP_GOODIES_EXPORT_HASH` or `NP_GOODIES_EXPORT_ALL` to
 *   be defined to be available in an exported dynamic library.
 *
 *  \see [Ayman El Didi](https://github.com/aeldidi/)'s [original version](https://github.com/aeldidi/crc32/) of \ref hash_crc32b. <i>(Public domain)</i>
 *  \see [extra/crc32_distribution_random.png](https://raw.githubusercontent.com/aziascreations/C99-Utility-Libraries/master/extra/crc32_distribution_random.png)
 *
 *  @{
 */

//-----------------------------------------------------------------------------
// The original `hash_crc32b` function was written by Ayman El Didi, and is
//  placed in the public domain.
// The code has been simplified and expanded in some ways to remove a function
//  call that was originally present for each byte and could slow the
//  calculation down, and to support the use of lookup tables.
//
// Source: https://github.com/aeldidi/crc32/
//-----------------------------------------------------------------------------

/**
 * Calculates the CRC32B hash of the `data_size` byte(s) long `data` buffer.
 * @param data Pointer to the data to be hashed
 * @param data_size Length of the buffer/data to be hashed.
 * @return The CRC32C hash.
 */
DLL_EXP_CRC32 uint32_t hash_crc32b(const char *data, size_t data_size);

// For CRC32C, see:
// * https://learn.microsoft.com/en-us/cpp/intrinsics/arm64-intrinsics?view=msvc-170
// * https://www.felixcloutier.com/x86/crc32

/** @} */ // end of group_crc32
