/// @file hashmap.c

#include <stdlib.h>

#include "hashmap.h"

#include "../../debug.h"

#define SIZE_MIN_CREATE 2
#define SIZE_MAX_CREATE 24

#define SIZE_MIN_SHRINK 2
#define SIZE_MAX_GROW 48

#define getMask(bitCount) ((0b1 << bitCount) - 1)

#define pow2(exponent) (2 << (exponent - 1))

/*
 * Benchmark-influenced choices:
 *  * Powers of two are calculated using `2 << (exponent - 1)` as `pow2(exponent)` instead of `pow(2, exponent)`.
 */

ChainedHashMap *hashmap_chained_create(uint8_t sizePower) {
	// The upper limit prevents massive allocations of >1GiB.
	if(sizePower <= SIZE_MIN_CREATE || sizePower > SIZE_MAX_CREATE) {
		error_println("Unable to create a chained hashmap with 2^x slots where x is <= 3 or >= 25 !");
		return NULL;
	}
	
	ChainedHashMap *newHashMap = malloc(sizeof(ChainedHashMap));
	
	if(newHashMap != NULL) {
		// Setting up basic pointers.
		newHashMap->entryCount = 0;
		
		// Setting the implementation-specific data's fields.
		newHashMap->sizePower = sizePower;
		newHashMap->buckets = calloc(pow2(sizePower), sizeof(ChainedHashMapBucket *));
		if(newHashMap->buckets == NULL) {
			free(newHashMap);
			return NULL;
		}
	}
	
	return newHashMap;
}

void *hashmap_chained_getByHash(ChainedHashMap *hashMap, uint64_t hash) {
	if(hashMap != NULL) {
		ChainedHashMapBucket *currentBucket =*hashMap->buckets[hash & getMask(hashMap->sizePower)];
		
		while(currentBucket != NULL) {
			if(currentBucket->hash == hash) {
				return currentBucket->data;
			}
			currentBucket = currentBucket->next;
		}
	}
	
	return NULL;
}

bool hashmap_chained_overwriteByHash(ChainedHashMap *hashMap, void* data, uint64_t hash,
									 void (*cb_freeData)(void *data)) {
	if(hashMap != NULL) {
		ChainedHashMapBucket *previousBucket = NULL;
		ChainedHashMapBucket *currentBucket = *hashMap->buckets[hash & getMask(hashMap->sizePower)];
		
		// We iterate over the bucket chain until we find a collision or an in-between.
		while(currentBucket != NULL) {
			if(currentBucket->hash >= hash) {
				break;
			}
			previousBucket = currentBucket;
			currentBucket = currentBucket->next;
		}
		
		if(currentBucket == NULL || currentBucket->hash != hash) {
			// We either reached the end of the list, or no buckets was in the current slot.
			// Or, we have an in-between, or we are at the start of the list.
			ChainedHashMapBucket *newBucket = malloc(sizeof(ChainedHashMapBucket));
			
			if(newBucket != NULL) {
				newBucket->next = currentBucket;
				newBucket->data = data;
				newBucket->hash = hash;
				
				if(previousBucket != NULL) {
					// In-between, or we are at the start of the list.
					previousBucket->next = newBucket;
				} else {
					// Start of the list.
					*hashMap->buckets[hash & getMask(hashMap->sizePower)] = newBucket;
				}
				
				hashMap->entryCount++;
				return true;
			}
		} else if(cb_freeData != NULL) {
			// Handling collision.
			cb_freeData(currentBucket->data);
			currentBucket->data = data;
			return true;
		}
		// Implied else: Handling collision while forbidden to overwrite => doing nothing.
	}
	
	return false;
}

void hashmap_chained_free(ChainedHashMap *hashMap, void (*cb_freeData)(void *data)) {
	if(hashMap != NULL) {
		// Freeing the buckets
		for(int i = 0; i < pow2(hashMap->sizePower); i++) {
			if(*hashMap->buckets[i] == NULL) {
				continue;
			}
			
			ChainedHashMapBucket *currentBucket = *hashMap->buckets[i];
			while(currentBucket != NULL) {
				ChainedHashMapBucket *nextBucket = currentBucket->next;
				
				if(currentBucket->data != NULL && cb_freeData != NULL) {
					cb_freeData(currentBucket->data);
				}
				free(currentBucket);
				
				currentBucket = nextBucket;
			}
		}
		
		free(hashMap->buckets);
		free(hashMap);
	}
}
