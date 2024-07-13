/// @file structs.h

#if !defined(NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_STRUCTS)
#define NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_STRUCTS

#include <stddef.h>
#include <stdint.h>

/** @addtogroup group_hashmap_chained
 *  @{
 */

/**
 * Chainable bucket used in \ref hashmap_chained "ChainedHashMap".
 */
typedef struct hashmap_chained_bucket ChainedHashMapBucket;

/**
 * Extension of the common \ref hashmap "HashMap" structure that implements the required fields for chained HashMaps.
 */
typedef struct hashmap_chained ChainedHashMap;

/**
 * Chainable bucket used in \ref hashmap_chained "ChainedHashMap".
 */
struct hashmap_chained_bucket {
	/**
	 * Data to be held as the bucket's data.
	 */
	void *data;
	
	/**
	 * Pointer to a potentially `NULL` next \ref hashmap_chained_bucket "ChainedHashMapBucket".
	 *
	 * If the pointer isn't `NULL`, the next hash will be arithmetically bigger.
	 */
	ChainedHashMapBucket *next;
	
	/**
	 * Original hash under which the data was inserted.
	 */
	uint64_t hash;
};

/**
 * Extension of the common \ref hashmap "HashMap" structure that implements the required fields for chained HashMaps.
 */
struct hashmap_chained {
	/**
	 * Amount of entries/buckets currently present in the list.
	 * \see \ref hashmap.entryCount "Original field in HashMap"
	 */
	size_t entryCount;
	
	/**
	 * Maximum amount of entries/buckets that can be inserted in the HashMap.
	 * @warning This value doesn't take entry/bucket chaining into account.
	 * \see \ref hashmap.capacity "Original field in HashMap"
	 */
	size_t capacity;
	
	/**
	 * Pointer to an array of \ref hashmap_chained_bucket "ChainedHashMapBucket" whose slots may be `NULL` if
	 *  not bucket is currently present.
	 *
	 * The array's size is defined by the `sizePower` field.<br>
	 * And indices for it should be bit-masked like so: `index & ((0b1 << sizePower) - 1)`
	 */
	ChainedHashMapBucket *(*buckets)[1];
	// The `1` stops errors and needless typecasts with array indices.
	// `buckets` being a pointer to an array of pointers saves ~16bytes per bucket.
	// If it was a pointer to an array of ChainedHashMapBucket, it would be 24bytes per array entry instead of 8.
	// It WILL use more memory on a full hashmap since you'd have 32 bytes per entry (8 for ptr & 24 for bucket).

	/**
	 * Amount of distinct entries/buckets slots are available in `buckets` represented as the exponent for
	 *  a power of two operation.<br>
	 * The amount can be calculated like so: `slots = 2 ^ sizePower`.
	 */
	uint8_t sizePower;
};

/** @} */ // end of group_hashmap_chained

#endif /* !NP_ONCE_C99_GOODIES_HASHMAP_CHAINED_STRUCTS */
