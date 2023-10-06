#include <stdio.h>

#include "../assert.h"

#include "../../src/hashmaps/chained/hashmap.h"

#define makeHash(bucketNumber, sortingSuffix) ((bucketNumber & 0b111) | (sortingSuffix << 3))

int main(void) {
	// Creating a hashmap with 8 buckets and some data.
	ChainedHashMap *testHashMap = hashmap_chained_create(3);
	assert(testHashMap != NULL, "HashMap was created successfully.")
	
	hashmap_chained_setByHash(testHashMap, (void *) 10, makeHash(2, 0));
	hashmap_chained_setByHash(testHashMap, (void *) 11, makeHash(2, 1));
	hashmap_chained_setByHash(testHashMap, (void *) 12, makeHash(2, 2));
	hashmap_chained_setByHash(testHashMap, (void *) 13, makeHash(2, 3));
	hashmap_chained_setByHash(testHashMap, (void *) 14, makeHash(2, 4));
	
	// Deleting the first.
	hashmap_chained_deleteByHash(testHashMap, makeHash(2, 0), NULL);
	assert((*testHashMap->buckets[2])->data == (void *) 11, "Bucket[2][0] is `11`.")
	assert(testHashMap->entryCount == 4, "HashMap now has 4 entries.")
	
	// Deleting the last.
	hashmap_chained_deleteByHash(testHashMap, makeHash(2, 4), NULL);
	assert((*testHashMap->buckets[2])->next->next->data == (void *) 13, "Bucket[2][2] is `13`.")
	assert((*testHashMap->buckets[2])->next->next->next == NULL, "Bucket[2][2] `next` is NULL.")
	assert(testHashMap->entryCount == 3, "HashMap now has 3 entries.")
	
	// Deleting the middle one.
	hashmap_chained_deleteByHash(testHashMap, makeHash(2, 2), NULL);
	assert((*testHashMap->buckets[2])->next != NULL, "Bucket[2][0] `nest` isn't NULL.")
	assert((*testHashMap->buckets[2])->next->data == (void *) 13, "Bucket[2][1] is `13`.")
	assert(testHashMap->entryCount == 2, "HashMap now has 2 entries.")
	
	// Cleaning Up.
	hashmap_chained_free(testHashMap, NULL);
	
	return 0;
}
