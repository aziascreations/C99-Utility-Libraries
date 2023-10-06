#include "utils.h"

float hash_getLoadFactor(HashMap *hashmap) {
	return (float) hashmap->entryCount / (float) hashmap->capacity;
}
