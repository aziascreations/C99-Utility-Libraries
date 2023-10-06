/// @file hashmap.h

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "structs.h"
#include "../structs.h"

#if defined(NP_GOODIES_EXPORT_HASHMAP_CHAINED) || defined(NP_GOODIES_EXPORT_HASHMAP_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXP_CHAINED_HASHMAP __declspec(dllexport)
#else
#define DLL_EXP_CHAINED_HASHMAP
#endif

/** @defgroup group_hashmap_chained Chained HashMap
 *
 *  TODO
 *
 *  @{
 */

/**
 *
 * @param sizePower
 * @return
 */
DLL_EXP_CHAINED_HASHMAP ChainedHashMap *hashmap_chained_create(uint8_t sizePower);

DLL_EXP_CHAINED_HASHMAP void *hashmap_chained_getByHash(ChainedHashMap *hashMap, uint64_t hash);

DLL_EXP_CHAINED_HASHMAP bool hashmap_chained_overwriteByHash(
		ChainedHashMap *hashMap,
		void* data,
		uint64_t hash,
		void (*cb_freeData)(void *data));

#define hashmap_chained_setByHash(hashMap, data, hash) (hashmap_chained_overwriteByHash(hashMap, data, hash, NULL))

////DLL_EXPORT bool hashmap_deleteByHash(HashMap *hashMap, void* key);

/**
 *
 * @param hashMap
 */
DLL_EXP_CHAINED_HASHMAP void hashmap_chained_free(ChainedHashMap *hashMap, void (*cb_freeData)(void *data));

/** @} */ // end of group_hashmap_chained
