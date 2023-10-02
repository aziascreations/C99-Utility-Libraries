/// @file structs.h

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define HASHMAP_TYPE_CHAINED 0b0000_0000

// See: https://en.wikipedia.org/wiki/Hash_table#Open_addressing
#define HASHMAP_TYPE_OPEN 0b0000_0001

typedef struct hashmap_vtable HashMapVirtualTable;
typedef struct hashmap HashMap;

/**
 * ??? C++ vtable
 *
 * This structure is used to centralise the implementation core functions by pointing to static versions of this
 *  structure instead of duplicating all the pointers in here in every hashmap.
 *
 * See: https://en.wikipedia.org/wiki/Virtual_method_table
 */
struct hashmap_vtable {
	/**
	 *
	 * @param hashMap
	 * @param hash An arbitrary hash ???
	 * @return
	 */
	void *(*get)(HashMap *hashMap, uint64_t hash);
	
	/**
	 *
	 * @param hashMap
	 * @param hash
	 * @return
	 */
	bool (*set)(HashMap *hashMap, uint64_t hash);
	
	/**
	 *
	 * @param hashMap
	 * @param hash
	 * @return
	 */
	bool (*delete)(HashMap *hashMap, uint64_t hash);
	
	/**
	 * Function used to free the hashmap itself and all its content using `cb_free`.
	 * @param data Pointer to data to be freed.
	 */
	void (*free)(HashMap *hashMap);
};

struct hashmap {
	/**
	 * ???
	 */
	const HashMapVirtualTable *vtable;
	
	// Fields
	//usedBucketCount
	
	// Callbacks
	/**
	 * Callback used to get an arbitrary hash for a given `item`.
	 * @param item
	 * @return The item's hash as a 64 bit/8 byte integer.
	 */
	uint64_t (*cb_hash)(const void *item);
	
	/**
	 * Callback used to free the user data in a bucket.
	 * If left as NULL, the data won't be freed.
	 * @param data Pointer to data to be freed.
	 */
	void (*cb_free)(void *data);
	
	// Make it optional and use the bucket's hash by default !
	//int (*cb_compare)(const void *a, const void *b);
	
	// TODO: Add conflict resolver callback
	
	// TODO: Add a "onLoadFactorReached".
	// TODO: Add a "onMaxBucketDepthReached".
	
	// Implementation-specific data
	
	/**
	 * Represents the type of HashMap.
	 * Used to differentiate between chained and open ones.
	 * If `#???` is used, it also helps with stricter checks when using the raw methods.
	 */
	uint8_t type;
	
	/**
	 * ???
	 */
	void *iData;
};

// nbBuckets, maxBuckets -> Derived from mask size !.
// Load factor = nbUsedBuckets / maxNbBuckets