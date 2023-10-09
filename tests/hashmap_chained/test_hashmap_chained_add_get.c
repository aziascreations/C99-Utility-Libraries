#include <stdio.h>

#include "../assert.h"

#include "../../src/hashmaps/chained/hashmap.h"

#define makeHash(bucketNumber, sortingSuffix) ((bucketNumber & 0b111) | (sortingSuffix << 3))

// Amounts to not freeing data when overwriting.
// It just avoids having the `hashmap_chained_overwriteByHash`
//  refusing to overwrite data if `cb_freeData` is NULL.
// This situation should only be encountered in tests.
void fakeFree(void *data) {}

int main(void) {
	// Creating a hashmap with 8 buckets.
	ChainedHashMap *testHashMap = hashmap_chained_create(3);
	assert(testHashMap != NULL, "HashMap was created successfully.")
	
	// Testing all insertions types in a single bucket.
	hashmap_chained_setByHash(testHashMap, (void *) 11, makeHash(0, 1)); // First
	hashmap_chained_setByHash(testHashMap, (void *) 13, makeHash(0, 3)); // Last
	hashmap_chained_setByHash(testHashMap, (void *) 10, makeHash(0, 0)); // New first
	hashmap_chained_setByHash(testHashMap, (void *) 14, makeHash(0, 4)); // New last
	hashmap_chained_setByHash(testHashMap, (void *) 12, makeHash(0, 2)); // Middle
	
	assert(testHashMap->entryCount == 5, "The hashmap has 5 entries.")
	assert((*testHashMap->buckets[0]) != NULL, "Bucket[0] isn't NULL.")
	
	assert((*testHashMap->buckets[0])->data == (void *) 10, "Bucket[0][0] is `10`.")
	assert((*testHashMap->buckets[0])->next->data == (void *) 11, "Bucket[0][1] is `11`.")
	assert((*testHashMap->buckets[0])->next->next->data == (void *) 12, "Bucket[0][2] is `12`.")
	assert((*testHashMap->buckets[0])->next->next->next->data == (void *) 13, "Bucket[0][3] is `13`.")
	assert((*testHashMap->buckets[0])->next->next->next->next->data == (void *) 14, "Bucket[0][4] is `14`.")
	
	// Testing non overwriting insertions.
	assert(!hashmap_chained_setByHash(testHashMap, (void *) 11, makeHash(0, 1)), "Unable to set existing [0][1].")
	assert(!hashmap_chained_setByHash(testHashMap, (void *) 13, makeHash(0, 3)), "Unable to set existing [0][3].")
	assert(!hashmap_chained_setByHash(testHashMap, (void *) 10, makeHash(0, 0)), "Unable to set existing [0][0].")
	assert(!hashmap_chained_setByHash(testHashMap, (void *) 14, makeHash(0, 4)), "Unable to set existing [0][4].")
	assert(!hashmap_chained_setByHash(testHashMap, (void *) 12, makeHash(0, 2)), "Unable to set existing [0][2].")
	
	// Testing all overwrite types in a single bucket.
	hashmap_chained_overwriteByHash(testHashMap, (void *) 110, makeHash(0, 1), &fakeFree);
	hashmap_chained_overwriteByHash(testHashMap, (void *) 130, makeHash(0, 3), &fakeFree);
	hashmap_chained_overwriteByHash(testHashMap, (void *) 140, makeHash(0, 4), &fakeFree);
	hashmap_chained_overwriteByHash(testHashMap, (void *) 120, makeHash(0, 2), &fakeFree);
	hashmap_chained_overwriteByHash(testHashMap, (void *) 100, makeHash(0, 0), &fakeFree);
	
	assert(testHashMap->entryCount == 5, "The hashmap still has 5 entries.")
	assert((*testHashMap->buckets[0]) != NULL, "Bucket[0] isn't NULL.")
	
	assert((*testHashMap->buckets[0])->data == (void *) 100, "Bucket[0][0] is `100`.")
	assert((*testHashMap->buckets[0])->next->data == (void *) 110, "Bucket[0][1] is `110`.")
	assert((*testHashMap->buckets[0])->next->next->data == (void *) 120, "Bucket[0][2] is `120`.")
	assert((*testHashMap->buckets[0])->next->next->next->data == (void *) 130, "Bucket[0][3] is `130`.")
	assert((*testHashMap->buckets[0])->next->next->next->next->data == (void *) 140, "Bucket[0][4] is `140`.")
	assert((*testHashMap->buckets[0])->next->next->next->next->next == NULL, "Bucket[0][4]'s `*next` is NULL.")
	
	// Adding data in buckets 1 to 7, with 1 overflow going back to 0.
	hashmap_chained_setByHash(testHashMap, (void *) 901, makeHash(1, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 902, makeHash(2, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 903, makeHash(3, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 904, makeHash(4, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 905, makeHash(5, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 906, makeHash(6, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 907, makeHash(7, 0b10000));
	hashmap_chained_setByHash(testHashMap, (void *) 908, makeHash(8, 0b10000));
	
	assert(testHashMap->entryCount == 13, "The hashmap still has 13 entries.")
	
	assert((*testHashMap->buckets[1])->data == (void *) 901, "Bucket[1][0] is `901`.")
	assert((*testHashMap->buckets[2])->data == (void *) 902, "Bucket[2][0] is `902`.")
	assert((*testHashMap->buckets[3])->data == (void *) 903, "Bucket[3][0] is `903`.")
	assert((*testHashMap->buckets[4])->data == (void *) 904, "Bucket[4][0] is `904`.")
	assert((*testHashMap->buckets[5])->data == (void *) 905, "Bucket[5][0] is `905`.")
	assert((*testHashMap->buckets[6])->data == (void *) 906, "Bucket[6][0] is `906`.")
	assert((*testHashMap->buckets[7])->data == (void *) 907, "Bucket[7][0] is `907`.")
	
	assert((*testHashMap->buckets[0])->next->next->next->next->next->data == (void *) 908, "Bucket[0][5] is `908`.")
	
	// Testing data addition via getter.
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 1)) == (void *) 110, "Getting 110 at [0][1]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 3)) == (void *) 130, "Getting 130 at [0][3]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 0)) == (void *) 100, "Getting 100 at [0][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 4)) == (void *) 140, "Getting 140 at [0][4]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 2)) == (void *) 120, "Getting 120 at [0][2]")
	
	assert(hashmap_chained_getByHash(testHashMap, makeHash(1, 0b10000)) == (void *) 901, "Getting 901 at [1][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(2, 0b10000)) == (void *) 902, "Getting 902 at [2][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(3, 0b10000)) == (void *) 903, "Getting 903 at [3][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(4, 0b10000)) == (void *) 904, "Getting 904 at [4][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(5, 0b10000)) == (void *) 905, "Getting 905 at [5][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(6, 0b10000)) == (void *) 906, "Getting 906 at [6][0]")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(7, 0b10000)) == (void *) 907, "Getting 907 at [7][0]")
	
	assert(hashmap_chained_getByHash(testHashMap, makeHash(8, 0b10000)) == (void *) 908, "Getting 908 at [0][5] with overflow")
	assert(hashmap_chained_getByHash(testHashMap, makeHash(0, 0b10000)) == (void *) 908, "Getting 908 at [0][5] without overflow")
	
	// Cleaning Up.
	hashmap_chained_free(testHashMap, NULL);
	
	return 0;
}
