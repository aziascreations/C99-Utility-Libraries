/// @file hashmap.c

#include <stdlib.h>

#include "hashmap.h"

HashMap *chainedHashmap_create() {
	HashMap *newHashMap = malloc(sizeof(HashMap));
	
	if(newHashMap != NULL) {
	
	}
	
	return newHashMap;
}

void chainedHashmap_free(HashMap *hashMap) {
	return;
}
