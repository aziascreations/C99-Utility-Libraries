/// @file structs.h

#pragma once

#include <stdint.h>

/** @addtogroup group_hashmap_chained
 *  @{
 */

typedef struct chainedHashmap_bucket ChainedHashMapBucket;

typedef struct hashmap_chained ChainedHashMap;

/**
 * Extension of `???` suited to support buckets in chained hashmaps
 */
struct chainedHashmap_bucket {
	/**
	 * Data to be held as the bucket's data.
	 */
	void *data;
	
	/**
	 * Pointer to a potentially `NULL` next \ref double_linked_list_node "DoubleLinkedListNode".
	 * TODO: Fix the ref !
	 */
	struct chainedHashmap_bucket *next;
	
	/**
	 * Original under which the data was inserted.
	 */
	uint64_t hash;
};

struct hashmap_chained {
	/**
	 * ???
	 * \see Original
	 */
	size_t entryCount;
	
	/**
	 * ???
	 * \see Original
	 */
	size_t capacity;
	
	// Implementation-specific data
	ChainedHashMapBucket *(*buckets)[1];  // The `1` stops errors and needless typecasts with array indices.
	// `buckets` being a pointer to an array of pointers saves ~16bytes per bucket.
	// If it was a pointer to an array of ChainedHashMapBucket, it would be 24bytes per array entry instead of 8.
	// It WILL use more memory on a full hashmap since you'd have 32 bytes per entry (8 for ptr & 24 for bucket).

	uint8_t sizePower;
};

/** @} */ // end of group_hashmap_chained
