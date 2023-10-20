/// @file hashmap.h

#if !defined(NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_MAIN)
#define NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_MAIN

#include <stdbool.h>
#include <stdint.h>

#include "../../platform.h"

#include "structs.h"
#include "../structs.h"

#if defined(NP_GOODIES_EXPORT_HASHMAP_CHAINED) || defined(NP_GOODIES_EXPORT_HASHMAP_ALL) || defined(NP_GOODIES_EXPORT_ALL)
	#define DLL_EXP_CHAINED_HASHMAP NP_DLL_EXPORT
#else
	#define DLL_EXP_CHAINED_HASHMAP
#endif

/** @defgroup group_hashmap_chained Chained HashMap
 *
 *  Chained HashMap implementation that builds off the \ref group_hashmap "HashMap Core module".
 *
 *  This type of HashMap has a pre-allocated array of `2 ^ n` pointers to potentially chaining
 *   \ref hashmap_chained_bucket "ChainedHashMapBucket".<br>
 *  In terms of memory efficiency, this type of internal structure becomes worse than an simple array of
 *   \ref hashmap_chained_bucket "ChainedHashMapBucket" once you pass the `0.75` load factor mark.
 *
 *  \see \ref group_hashmap "HashMap Core module"
 *  \see https://en.wikipedia.org/wiki/Hash_table#Separate_chaining
 *
 *  @{
 */

/**
 * Creates an empty \ref hashmap_chained "ChainedHashMap" with `2 ^ sizePower` slots for
 *  \ref hashmap_chained_bucket "ChainedHashMapBucket".
 * @param sizePower Amount of distinct bucket slots to be available represented as the exponent for
 *                   a power of two operation.<br>
 *                  The size must inclusively be between `2` and `23`, which limits the slots count
 *                   from `4` to `8,388,608` !
 * @return The newly created \ref hashmap_chained "ChainedHashMap", or `NULL` if the size was invalid.
 */
DLL_EXP_CHAINED_HASHMAP ChainedHashMap *hashmap_chained_create(uint8_t sizePower);

/**
 * Returns the data belonging to a \ref hashmap_chained_bucket "ChainedHashMapBucket" whose hash
 *  matches the given one.
 * @param hashMap The relevant \ref hashmap_chained "ChainedHashMap".
 * @param hash The desired data's hash.
 * @return The desired data pointer, or `NULL` is no buckets with a matching hash were found.
 */
DLL_EXP_CHAINED_HASHMAP void *hashmap_chained_getByHash(ChainedHashMap *hashMap, uint64_t hash);

/**
 * Inserts and potentially overwrites a conflicting entry into the given \ref hashmap_chained "ChainedHashMap" with
 *  the given hash.
 * @param hashMap The relevant \ref hashmap_chained "ChainedHashMap".
 * @param data A pointer to the inserted data.
 * @param hash The data's hash.
 * @param cb_freeData A function that will free the \ref hashmap_chained_bucket "ChainedHashMapBucket"'s data.<br>
 *                    If left as `NULL`, the data won't be inserted !
 * @return <code>true</code> if it was inserted properly, <code>false</code> otherwise.
 */
DLL_EXP_CHAINED_HASHMAP bool hashmap_chained_overwriteByHash(
		ChainedHashMap *hashMap,
		void* data,
		uint64_t hash,
		void (*cb_freeData)(void *data));

/**
 * Inserts an entry into the given \ref hashmap_chained "ChainedHashMap" with the given hash if no conflict is found.
 * @param hashMap The relevant \ref hashmap_chained "ChainedHashMap".
 * @param data A pointer to the inserted data.
 * @param hash The data's hash.
 * @return <code>true</code> if it was inserted properly, <code>false</code> if there was an error or conflict.
 */
#define hashmap_chained_setByHash(hashMap, data, hash) (hashmap_chained_overwriteByHash(hashMap, data, hash, NULL))

/**
 * Removed an entry from the given \ref hashmap_chained "ChainedHashMap" with the given hash using a custom callback
 *  to free the removed \ref hashmap_chained_bucket "ChainedHashMapBucket"'s data.
 * @param hashMap The relevant \ref hashmap_chained "ChainedHashMap".
 * @param hash The removed data's hash.
 * @param cb_freeData A function that will free the \ref hashmap_chained_bucket "ChainedHashMapBucket"'s data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @return <code>true</code> if it was removed properly, <code>false</code> if it couldn't be found.
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_CHAINED_HASHMAP bool hashmap_chained_deleteByHash(
		ChainedHashMap *hashMap,
		uint64_t hash,
		void (*cb_freeData)(void *data));

/**
 * Frees a \ref hashmap_chained "ChainedHashMap" and all its \ref hashmap_chained_bucket "ChainedHashMapBucket" using
 *  a custom callback to free the \ref hashmap_chained_bucket "ChainedHashMapBucket"'s data.
 * @param hashMap The freed \ref hashmap_chained "ChainedHashMap".
 * @param cb_freeData A function that will free the \ref hashmap_chained_bucket "ChainedHashMapBucket"'s data.<br>
 *                    If left as `NULL`, the data won't be freed !
 * @warning May cause memory leaks if `cb_freeData` is NULL.
 */
DLL_EXP_CHAINED_HASHMAP void hashmap_chained_free(ChainedHashMap *hashMap, void (*cb_freeData)(void *data));

/** @} */ // end of group_hashmap_chained

#endif /* !NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_MAIN */
