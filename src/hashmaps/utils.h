#pragma once

#include "structs.h"

/**
 * Returns the load factor of the given \ref hashmap "HashMap" as ???.
 * @param hashmap
 * @return The HashMap's load factor as a `float` between `0.0` and `1.0`.
 */
float hash_getLoadFactor(HashMap *hashmap);
