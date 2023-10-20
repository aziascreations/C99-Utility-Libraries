/// @file utils.h

#if !defined(NP_ONCE_C99_GOODIES_HASHMAP_COMMONS_UTILS)
#define NP_ONCE_C99_GOODIES_HASHMAP_COMMONS_UTILS

#include "structs.h"

/** @defgroup group_hashmap HashMap Core
 *
 *  Common set of structures and utilities that is shared by all HashMap implementations.
 *
 *  @{
 */

/**
 * Returns the load factor of the given \ref hashmap "HashMap" as a ratio of the amount of buckets in the
 *  \ref hashmap "HashMap" over the maximum amount of slots available in the HashMap.
 * @param hashmap Evaluated \ref hashmap "HashMap".
 * @return The HashMap's load factor as a `float` between `0.0` and `1.0`.
 */
float hashmap_getLoadFactor(HashMap *hashmap);

/** @} */ // end of group_hashmap

#endif /* !NP_ONCE_C99_GOODIES_HASHMAP_COMMONS_UTILS */
