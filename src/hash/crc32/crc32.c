/// @file crc32.c

#include "crc32.h"

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
