/// @file crc32.h

#pragma once

#if defined(NP_GOODIES_EXPORT_CRC32) || defined(NP_GOODIES_EXPORT_HASH) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include <stdint.h>

//-----------------------------------------------------------------------------
// The original `hash_crc32b` function was written by Ayman El Didi, and is
//  placed in the public domain.
//
// The code has been simplified to remove a function call that was originally
//  present for each byte and could slow the calculation down.
//
// Source: https://github.com/aeldidi/crc32/
//-----------------------------------------------------------------------------

/**
 * Calculates the CRC32B hash of the `data_size` byte(s) long `data` buffer.
 * @param data Pointer to the data to be hashed
 * @param data_size Length of the buffer/data to be hashed.
 * @return The CRC32C hash.
 */
DLL_EXPORT uint32_t hash_crc32b(const char *data, size_t data_size);

// For CRC32C, see:
// * https://learn.microsoft.com/en-us/cpp/intrinsics/arm64-intrinsics?view=msvc-170
// * https://www.felixcloutier.com/x86/crc32
