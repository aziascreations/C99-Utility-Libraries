/// @file hashmap.h

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "structs.h"
#include "../structs.h"

#if defined(NP_GOODIES_EXPORT_HASHMAP_ALL) || defined(NP_GOODIES_EXPORT_ALL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/**
 *
 * @param sizePower
 * @param cb_hash
 * @param cb_free
 * @return
 */
DLL_EXPORT HashMap *hashmap_chained_create(
		uint8_t sizePower,
		uint64_t (*cb_hash)(const void *item),
		void (*cb_free)(void *data)
);

//DLL_EXPORT HashMap *hashmap_create();
//
//DLL_EXPORT void hashmap_free(HashMap *hashMap);
//
//DLL_EXPORT void *hashmap_get(HashMap *hashMap, void* key);
//DLL_EXPORT void *hashmap_getByHash(HashMap *hashMap, uint64_t hash);
//
//DLL_EXPORT bool hashmap_set(HashMap *hashMap, void* data, void* key);
//DLL_EXPORT bool hashmap_setByHash(HashMap *hashMap, void* data, uint64_t hash);
//
//DLL_EXPORT bool hashmap_delete(HashMap *hashMap, void* key);
//DLL_EXPORT bool hashmap_deleteByHash(HashMap *hashMap, uint64_t hash);

// TODO: Add one to remove and return the pointer without freeing ?

DLL_EXPORT void hashmap_chained_free(HashMap *hashMap);

/**
 * Vtable thingy.
 */
static const HashMapVirtualTable _hashmap_chained_vtable = {
		.get = NULL,
		.set = NULL,
		.delete = NULL,
		.free = hashmap_chained_free,
};
