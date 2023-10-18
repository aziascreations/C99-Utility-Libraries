/** @file */

#include "uuid4.h"

/** @addtogroup group_uuid
 *  @{
 */

UUID4 *uuid4_generate(bool (*cb_randomFillBuffer)(void *buffer, size_t length)) {
	// C99-compatible compile-time check for the UUID4 structure's size.
	NP_GOODIES_UUID_CHECK_STRUCT_SIZE(sizeof(UUID4) != UUID_BYTE_LENGTH);
	
	// Sanity check
	if(cb_randomFillBuffer == NULL) {
		return NULL;
	}
	
	// Allocating memory to the buffer.
	UUID4 *returnedUUID4 = malloc(UUID_BYTE_LENGTH);
	
	if(returnedUUID4 != NULL) {
		// Filling the buffer with random data.
		if(!cb_randomFillBuffer(returnedUUID4, UUID_BYTE_LENGTH)) {
			free(returnedUUID4);
			return NULL;
		}
		
		// Setting the variant bits as 0b100 or 0b101.
		// The value indicates that the variant comes from the RFC.
		((uint8_t*) returnedUUID4)[9] = (((uint8_t*) returnedUUID4)[9] & 0b00011111) | (((uint8_t) rand()) % 2 ? 0b10000000 : 0b10100000);
		
		// Setting the version bits as 0b0100.
		((uint8_t*) returnedUUID4)[7] = (((uint8_t*) returnedUUID4)[7] & 0b00001111) | 0b01000000;
	}
	
	return returnedUUID4;
}

/** @} */ // end of group_uuid
