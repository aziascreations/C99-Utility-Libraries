/** @file */

#if !defined(NP_ONCE_C99_GOODIES_UUID_STRUCTS)
#define NP_ONCE_C99_GOODIES_UUID_STRUCTS

#include <stdint.h>

/**
 *  Main packed structure that contains a UUID4's data.<br>
 *  It is used instead of a buffer to make it easier to access parts of it.
 *
 *  This structure is also available as the following typedef name: `UUID4`
 *
 *  <b>Warning:</b><br>
 *  This structure may not be packed properly depending on the compiler you use.<br>
 *  Check the \ref group_uuid "UUID module"'s description for more information on that.
 *
 *  \see group_uuid
 *  \see https://en.wikipedia.org/wiki/Universally_unique_identifier
 *  \see https://www.rfc-editor.org/rfc/rfc4122
 */
struct uuid {
	/**
	 * The low field of the timestamp.
	 */
	uint32_t time_low;
	
	/**
	 * The low middle of the timestamp.
	 */
	uint16_t time_mid;
	
	/**
	 * The high field of the timestamp multiplexed with the version number.
	 */
	uint16_t time_hi_and_version;
	
	/**
	 * The high field of the clock sequence multiplexed with the variant.
	 */
	uint16_t clock_seq_hi_and_reserved;
	
	/**
	 * First double word of the *48-bit node id*.
	 */
	uint16_t node_dword1;
	
	/**
	 * Second double word of the *48-bit node id*.
	 */
	uint16_t node_dword2;
	
	/**
	 * Third and last double word of the *48-bit node id*.
	 */
	uint16_t node_dword3;
};
// __attribute__((packed))
typedef struct uuid UUID4;


// Asserting that the struct has the correct size.
// This will result in zero code if it compiles.
// Source: https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/

#ifndef NP_GOODIES_UUID_DISABLE_STRUCT_SIZE_CHECK
#define NP_GOODIES_UUID_CHECK_STRUCT_SIZE(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#else
#define NP_GOODIES_UUID_CHECK_STRUCT_SIZE(condition)
#endif

#endif /* !NP_ONCE_C99_GOODIES_UUID_STRUCTS */
