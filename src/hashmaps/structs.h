/// @file structs.h

#pragma once

#include <stdint.h>
#include <stdbool.h>

/** @addtogroup group_hashmap
 *  @{
 */

/**
 * Shared base that gets extended by all HashMap implementations.
 */
typedef struct hashmap HashMap;

/**
 * Shared base that gets extended by all HashMap implementations.
 */
struct hashmap {
	/**
	 * Amount of entries/buckets currently present in the list.
	 */
	size_t entryCount;
	
	/**
	 * Maximum amount of entries/buckets that can be inserted in the HashMap.
	 * @warning This value doesn't take entry/bucket chaining into account.
	 */
	size_t capacity;
};

/** @} */ // end of group_hashmap
