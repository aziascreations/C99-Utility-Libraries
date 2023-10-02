/** @file */

#include "crc32.h"

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

// Notes:

// Can be used for crc32c, not crc32b
//#include "intrin.h"

//-----------------------------------------------------------------------------
// The original `hash_crc32b` function was written by Ayman El Didi, and is
//  placed in the public domain.
//
// The code has been simplified to remove a function call that was originally
//  present for each byte.
//
// Source: https://github.com/aeldidi/crc32/
//-----------------------------------------------------------------------------

uint32_t hash_crc32b(const char *data, size_t data_size) {
	uint32_t crc32 = 0xFFFFFFFF;
	
	for(size_t data_offset = 0; data_offset < data_size; data_offset++) {
		crc32 ^= data[data_offset];
		
		for(size_t bit_offset = 0; bit_offset < 8; bit_offset++) {
			crc32 = (crc32 >> 1) ^ (crc32 & 1) * 0xEDB88320;
		}
	}
	
	return ~crc32;
}

/** @} */ // end of group_crc32
