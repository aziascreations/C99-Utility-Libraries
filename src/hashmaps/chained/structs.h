/// @file structs.h

#pragma once

//#include <stdint.h>

#include "../structs.h"

typedef struct chainedHashmap_bucket ChainedHashMapBucket;

typedef struct hashmap_chained_implementation_data ChainedHashMapData;

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

struct hashmap_chained_implementation_data {
	ChainedHashMapBucket *(*buckets)[1];  // The `1` stops errors and needless typecasts with array indices.
	
	// `buckets` being a pointer to an array of pointers saves ~16bytes per bucket.
	// If it was a pointer to an array of ChainedHashMapBucket, it would be 24bytes per array entry instead of 8.
	// It WILL use more memory on a full hashmap since you'd have 32 bytes per entry (8 for ptr & 24 for bucket).
	
	// THIS IS WRONG !
	//// However, chained hashmaps tend to shit the bed in terms of performances at around 0.75 load factor which is
	////  exactly the point where the current method would start taking more memory than the alternative.
	//// This is also the point at which you'd be encouraged to grow the hashmap and kick the can down the road at
	////  the same time.
	
	// Also, it turns out that not using single linked lists for each bucket chain saves a shit-ton of memory.
	// I revamped the entire list module for nothing...  At least for now...  It's still 5 days of motivation down the drain, sorta...
	
	uint8_t sizePower;
};
