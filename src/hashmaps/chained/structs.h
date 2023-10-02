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
	//uint64_t hash;
};

struct hashmap_chained_implementation_data {
	
	//ChainedHashMapBucket* buckets[];
};
