/// @file structs.h

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct hashmap HashMap;

struct hashmap {
	/**
	 * ???
	 */
	size_t entryCount;
	
	/**
	 * ???
	 */
	size_t capacity;
};

// nbBuckets, maxBuckets -> Derived from mask size !.
// Load factor = nbUsedBuckets / maxNbBuckets

// TODO: Make definition to have macros OR functions.

// TODO: Use macros to have something like hashmap_set(hashmap, data) => hashmap->vtable->set(hashmap, data), & key !
//#define hashmap_set(hashmap, key, value) hashmap->vtable->set();
