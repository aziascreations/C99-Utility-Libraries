#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../assert.h"
#include "../memutils.h"

#include "../../src/hashmaps/chained/hashmap.h"

int main(void) {
	ChainedHashMap *testHashMap;
	
	assert(offsetof(HashMap, entryCount) == offsetof(ChainedHashMap, entryCount),
		   "HashMap and ChainedHashMap have the same offset for `entryCount`.")
	assert(offsetof(HashMap, capacity) == offsetof(ChainedHashMap, capacity),
		   "HashMap and ChainedHashMap have the same offset for `capacity`.")
	
	assert(hashmap_chained_create(2) == NULL, "HashMap can't be created with `2^2 slots`")
	assert(hashmap_chained_create(25) == NULL, "HashMap can't be created with `2^25 slots`")
	
	// Testing minimal size
	testHashMap = hashmap_chained_create(4);
	assert(testHashMap != NULL, "HashMap was created successfully.")
	
	assert(testHashMap->entryCount == 0, "HashMap's item count is `0`")
	
	assert(testHashMap->sizePower == 4, "HashMap's iData's `sizePower` is `4`.")
	assert(testHashMap->buckets != NULL, "HashMap's iData's `buckets` isn't NULL.")
	assert(memUtils_getSize(testHashMap->buckets) == pow(2, 4) * sizeof(ChainedHashMapBucket *),
		   "HashMap's iData's `buckets` is 128 bytes long, via dynamic calculation. ((2^4)*8)")
	assert(memUtils_getSize(testHashMap->buckets) == 128,
		   "HashMap's iData's `buckets` is 128 bytes long, via direct number. ((2^4)*8)")
	
	bool areAllPointersNull = true;
	for(int i = 0; i < pow(2, 4); i++) {
		if(*testHashMap->buckets[i] != NULL) {
			printf("%p\n", *testHashMap->buckets[i]);
			printf("%d\n", i);
			areAllPointersNull = false;
			break;
		}
	}
	assert(areAllPointersNull, "HashMap's iData's `buckets` only has NULL entries.")
	
	hashmap_chained_free(testHashMap, &free);
	
	return 0;
}
