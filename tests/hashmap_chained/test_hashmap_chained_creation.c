#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../assert.h"
#include "../memutils.h"

#include "../../src/hashmaps/chained/hashmap.h"

uint64_t cb_hash_test(const void *item) {
	return 0;
}

int main(void) {
	HashMap *testHashMap;
	
	assert(hashmap_chained_create(2, &cb_hash_test, &free) == NULL, "HashMap can't be created with `2^2 slots`")
	assert(hashmap_chained_create(25, &cb_hash_test, &free) == NULL, "HashMap can't be created with `2^25 slots`")
	
	assert(hashmap_chained_create(8, NULL, &free) == NULL, "HashMap can't be created without `cb_hash`")
	assert(hashmap_chained_create(8, &cb_hash_test, NULL) == NULL, "HashMap can't be created without `cb_free`")
	
	// Testing minimal size
	testHashMap = hashmap_chained_create(4, &cb_hash_test, &free);
	assert(testHashMap != NULL, "HashMap was created successfully.")
	
	assert(testHashMap->cb_hash == &cb_hash_test, "HashMap's `*cb_hash` is correct.")
	assert(testHashMap->cb_free == &free, "HashMap's `*cb_free` is correct.")
	assert(testHashMap->entryCount == 0, "HashMap's item count is `0`")
	
	// FIXME: Find out why the pointers aren't the same. (Different from &vtable in .h file, but == across instances)
	//assert(testHashMap->vtable == &_hashmap_chained_vtable, "Test 01")
	assert(testHashMap->vtable->get == _hashmap_chained_vtable.get, "HashMap's vtable's `get` pointer is correct.")
	assert(testHashMap->vtable->set == _hashmap_chained_vtable.set, "HashMap's vtable's `set` pointer is correct.")
	assert(testHashMap->vtable->delete == _hashmap_chained_vtable.delete, "HashMap's vtable's `delete` pointer is correct.")
	assert(testHashMap->vtable->free == _hashmap_chained_vtable.free, "HashMap's vtable's `free` pointer is correct.")
	
	ChainedHashMapData *iData = testHashMap->iData;
	assert(iData->sizePower == 4, "HashMap's iData's `sizePower` is `4`.")
	assert(iData->buckets != NULL, "HashMap's iData's `buckets` isn't NULL.")
	assert(memUtils_getSize(iData->buckets) == pow(2, 4) * sizeof(ChainedHashMapBucket *), "HashMap's iData's `buckets` is 128 bytes long, via dynamic calculation. ((2^4)*8)")
	assert(memUtils_getSize(iData->buckets) == 128, "HashMap's iData's `buckets` is 128 bytes long, via direct number. ((2^4)*8)")
	
	bool areAllPointersNull = true;
	for(int i = 0; i < pow(2, 4); i++) {
		if(*iData->buckets[i] != NULL) {
			printf("%p\n", *iData->buckets[i]);
			printf("%d\n", i);
			areAllPointersNull = false;
			break;
		}
	}
	assert(areAllPointersNull, "HashMap's iData's `buckets` only has NULL entries.")
	
	hashmap_chained_free(testHashMap);
	
	return 0;
}
