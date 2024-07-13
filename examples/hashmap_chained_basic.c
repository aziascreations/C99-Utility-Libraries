#include <stdio.h>
#include <stdlib.h>

#include "../src/hashmaps/chained/hashmap.h"
#include "../src/hash/crc32/crc32.h"
#include "../src/text.h"

// Preparing a list of data to insert in the HashMap.
// We're using 'char' strings to reliably predict their hash.
// Said hash can be seen next to them and will contain collisions for example purposes.
static const char *dataEntries[] = {
		// Regular non colliding keys that end up in individual buckets.
		"Hello World",  // 0x4a17b156
		"I'm glad to",  // 0xb07b8fb2
		"meet you :)",  // 0x02a22b34
		
		// Will end up in the same bucket as "meet you :)"
		"weeeeee :D",  // 0xc9288314
		
		// These 2 keys will have a perfect collision.
		"COLLISION",  // 0x1f0f3d51
		"w7Rfb",      // 0x1f0f3d51
};
static const int dataCount = 6;

int main() {
	// Creating a Chained HashMap with 16 buckets (2 ^ 4).
	// The low size will help create collisions and show that it supports them.
	ChainedHashMap *hashmap = hashmap_chained_create(4);
	if(hashmap == NULL) {
		printf("Fatal error: Failed to create HashMap !");
		return 1;
	}
	
	printf("Printing out input data...\n");
	for(int i = 0; i < dataCount; i++) {
		printf("  0x%08x <-> \"%s\"\n", hash_crc32b(dataEntries[i], text_strlenA(dataEntries[i])), dataEntries[i]);
	}
	
	printf("Inserting data...\n");
	for(int i = 0; i < dataCount; i++) {
		// We make a copy of the input string in order to be able to free it later on.
		// While not required in this example, it helps illustrate proper freeing behaviour in the end.
		char *copiedData = text_copyA(dataEntries[i]);
		
		if(copiedData == NULL) {
			printf("Fatal error: Unable to copy string !\n");
			return 2;
		}
		
		// We attempt to insert the strings.
		// This functions prevents overwrites when encountering a collision.
		if(!hashmap_chained_setByHash(hashmap, copiedData, hash_crc32b(copiedData, text_strlenA(copiedData)))) {
			printf("  Failed to insert \"%s\", likely due to collision or malloc error !\n", copiedData);
			
			// In this example, we'll overwrite the existing data its colliding with.
			// This function can be used in lieu of "hashmap_chained_setByHash" to insert stuff into the HashMap.
			// The only difference is that we give it a function pointer to use when it needs to free existing data
			//  in the event of a collision.
			if(!hashmap_chained_overwriteByHash(hashmap, copiedData, hash_crc32b(copiedData, text_strlenA(copiedData)), &free)) {
				printf("  Failed to insert \"%s\", very likely due a malloc error !\n", copiedData);
				free(copiedData);
			} else {
				printf("  The data that collided with \"%s\" has been overwritten !\n", copiedData);
			}
		}
	}
	
	printf("Getting data using functions...\n");
	for(int i = 0; i < dataCount; i++) {
		uint32_t keyHash = hash_crc32b(dataEntries[i], text_strlenA(dataEntries[i]));
		printf("  Key:\"%s\"\tCRC32:0x%08x\tData:\"%s\"\n",
			   dataEntries[i],
			   keyHash,
			   (char *) hashmap_chained_getByHash(hashmap, keyHash));
	}
	
	// Freeing the HashMap and its resources using the standard `free()` function.
	// If you hadn't copied the strings and referenced their pointer directly, you
	//  should have changed `&free` to `NULL` as they cannot be freed.
	hashmap_chained_free(hashmap, &free);
}
