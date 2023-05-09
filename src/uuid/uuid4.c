/// @file uuid4.c

#include "uuid4.h"

/** @addtogroup group_uuid
 *  @{
 */

UUID4 *uuid4_generate() {
	// C99-compatible compile-time check for the UUID4 structure's size.
	NP_UUID_CHECK_STRUCT_SIZE(sizeof(UUID4) != UUID_BYTE_LENGTH);
	
	// Allocating memory to the buffer.
	UUID4 *returnedUUID4 = malloc(UUID_BYTE_LENGTH);
	
	if(returnedUUID4 != NULL) {
		// Filling the UUID4 buffer with random data first.
		// Notes:
		//   * A compiler "#if" is used to optimize the random population.
		//   * However, the highest value I found for `RAND_MAX` was 0x7FFFFFFF which means it's not long enough to
		//      populate 4 bytes fully, which is therefore not fully tested, but should be working properly.
#if RAND_MAX >= 0xFFFFFFFF
		// We can generate 4 full bytes randomly. (Untested !!!)
		for(short i = 0; i < UUID_BYTE_LENGTH / 4; i++) {
			((uint32_t*) returnedUUID4)[i] = (uint32_t) rand();
		}
#elif RAND_MAX >= 0xFFFF
		// We can generate 2 full bytes randomly.
		for(short i = 0; i < UUID_BYTE_LENGTH / 2; i++) {
			((uint16_t*) returnedUUID4)[i] = (uint16_t) rand();
		}
#else
		// We can generate a full byte randomly.
		for(short i = 0; i < UUID_BYTE_LENGTH; i++) {
			((uint8_t*) returnedUUID4)[i] = (uint8_t) rand();
		}
#endif
		
		// Setting the variant bits as 0b100 or 0b101.
		// The value indicates that the variant comes from the RFC.
		((uint8_t*) returnedUUID4)[9] = (((uint8_t*) returnedUUID4)[9] & 0b00011111) | (((uint8_t) rand()) % 2 ? 0b10000000 : 0b10100000);
		
		// Setting the version bits as 0b0100.
		((uint8_t*) returnedUUID4)[7] = (((uint8_t*) returnedUUID4)[7] & 0b00001111) | 0b01000000;
	}
	
	return returnedUUID4;
}

/** @} */ // end of group_uuid
