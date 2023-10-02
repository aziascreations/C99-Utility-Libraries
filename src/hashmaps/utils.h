#pragma once

#include "structs.h"

// What ?
//#define hashmap_getTest(hashmap, key) (hashmap->getStuff(key))

/**
 * Returns the load factor of the given \ref hashmap "HashMap" as ???.
 * @param hashmap
 * @return
 */
float hash_getLoadFactor(HashMap *hashmap);
