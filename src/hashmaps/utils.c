#include "utils.h"

float hashmap_getLoadFactor(HashMap *hashmap) {
	return (float) hashmap->entryCount / (float) hashmap->capacity;
}
