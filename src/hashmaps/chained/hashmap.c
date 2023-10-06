/// @file hashmap.c

#include <stdlib.h>

#include "hashmap.h"

#include "../../debug.h"

#define SIZE_MIN_CREATE 2
#define SIZE_MAX_CREATE 24

#define SIZE_MIN_SHRINK 2
#define SIZE_MAX_GROW 48

#define getMask(bitCount) ((0b1 << bitCount) - 1)

/*
 * Benchmark-influenced choices:
 *  * Powers of two are calculated using `2 << (exponent - 1)` instead of `pow()`.
 */

HashMap *hashmap_chained_create(uint8_t sizePower,
								uint64_t (*cb_hash)(const void *item),
								void (*cb_free)(void *data)) {
	// The callbacks cannot be NULL.
	if(cb_hash == NULL || cb_free == NULL) {
		error_println("Unable to create a chained hashmap with one their callbacks being NULL !");
		return NULL;
	}
	
	// The upper limit prevents massive allocations of >1GiB.
	if(sizePower <= SIZE_MIN_CREATE || sizePower > SIZE_MAX_CREATE) {
		error_println("Unable to create a chained hashmap with 2^x slots where x is <= 3 or >= 25 !");
		return NULL;
	}
	
	HashMap *newHashMap = malloc(sizeof(HashMap));
	
	if(newHashMap != NULL) {
		// Setting up basic pointers.
		newHashMap->vtable = &_hashmap_chained_vtable;
		newHashMap->cb_hash = cb_hash;
		newHashMap->cb_free = cb_free;
		newHashMap->entryCount = 0;
		
		// Setting up implementation-specific data.
		newHashMap->iData = malloc(sizeof(ChainedHashMapData));
		if(newHashMap->iData == NULL) {
			free(newHashMap);
			return NULL;
		}
		
		// Setting the implementation-specific data's fields.
		((ChainedHashMapData *) (newHashMap->iData))->sizePower = sizePower;
		((ChainedHashMapData *) (newHashMap->iData))->buckets = calloc(2 << (sizePower - 1), sizeof(ChainedHashMapBucket *));
		if(((ChainedHashMapData *) (newHashMap->iData))->buckets == NULL) {
			free(newHashMap->iData);
			free(newHashMap);
			return NULL;
		}
	}
	
	return newHashMap;
}

void hashmap_chained_free(HashMap *hashMap) {
	if(hashMap != NULL) {
		// Freeing the buckets
		ChainedHashMapData* iData= hashMap->iData;
		for(int i = 0; i < (2 << (iData->sizePower - 1)); i++) {
			if(iData->buckets[i] == NULL) {
				continue;
			}
			
			ChainedHashMapBucket *currentBucket = *iData->buckets[i];
			while(currentBucket != NULL) {
				ChainedHashMapBucket *nextBucket = currentBucket->next;
				
				if(currentBucket->data != NULL) {
					hashMap->cb_free(currentBucket->data);
				}
				free(currentBucket);
				
				currentBucket = nextBucket;
			}
		}
		
		free(hashMap->iData);
		free(hashMap);
	}
}
