/** @file */

#include "uuid.h"

/** @defgroup group_uuid UUID
 *
 *  <b>Warning:</b><br>
 *  The \ref uuid4_generate function uses the \ref https://cplusplus.com/reference/cstdlib/rand/ "rand" function internally in
 *   order to remain compatible with C99.<br>
 *  You **MUST** call \ref https://cplusplus.com/reference/cstdlib/srand/ "srand" before generating any UUID if you
 *   want random UUIDs and not the same sequence than ones generated in previous executions.<br>
 *  If a more secure random number generator is required, you should seek out other implementations of UUID4 generators
 *   since C99 and C11 only support `rand` and `srand` as far as I could tell.
 *
 *  The \ref uuid structure isn't explicitly packed since MSVC seems to struggle with the `__attribute__((packed))` directive.<br>
 *  However, the size of said structure is checked at compile time and raises an error if it ain't right.<br>
 *  This check can be disabled by defining the `NP_UUID_DISABLE_STRUCT_SIZE_CHECK` constant during compilation in order
 *   to leave the \ref uuid structure with an invalid size.<br>
 *  None of the module's function use `sizeof(uuid)` or explicitly use on of the structure's fields so its safe to use
 *   as long as **you** don't use them either.
 *
 *  It should be noted that while using MSVC, the structure should always be aligned properly since the maximum it can
 *   do by default is every 16 bytes.<br>
 *  See \ref https://learn.microsoft.com/en-us/cpp/build/reference/zp-struct-member-alignment "MS C compiler /Zp flag documentation"
 *   for more info.
 *
 *  Unless `NP_WIN32` is defined, all functions that uses or return a `wchar_t` typed variable won't be accessible.<br>
 *  This is due to the fact that `wchar_t` is only accessible easily on Windows platforms.
 *
 *  \see uuid
 *  \see https://en.wikipedia.org/wiki/Universally_unique_identifier
 *  \see https://www.rfc-editor.org/rfc/rfc4122
 *  \see https://cplusplus.com/reference/cstdlib/rand/
 *  \see https://learn.microsoft.com/en-us/cpp/build/reference/zp-struct-member-alignment
 *  @{
 */

char *uuid_toString(UUID4 *uuid) {
	// C99-compatible compile-time check for the UUID4 structure's size.
	NP_GOODIES_UUID_CHECK_STRUCT_SIZE(sizeof(UUID4) != UUID_BYTE_LENGTH);
	
	char *uuidString = NULL;
	
	if(uuid != NULL) {
		uuidString = malloc(sizeof(char) * (UUID_CHAR_COUNT + 1));
		
		if(uuidString != NULL) {
			#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
			if(sprintf_s(uuidString, UUID_CHAR_COUNT + 1, "%08X-%04X-%04X-%04X-%04X%04X%04X",
						 ((uint32_t *)uuid)[0], ((uint16_t *)uuid)[2], ((uint16_t *)uuid)[3], ((uint16_t *)uuid)[4],
						 ((uint16_t *)uuid)[5], ((uint16_t *)uuid)[6], ((uint16_t *)uuid)[7]) < 0) {
				free(uuidString);
				uuidString = NULL;
			}
			#else
			if(sprintf(uuidString, "%08X-%04X-%04X-%04X-%04X%04X%04X",
					   ((uint32_t *)uuid)[0], ((uint16_t *)uuid)[2], ((uint16_t *)uuid)[3], ((uint16_t *)uuid)[4],
					   ((uint16_t *)uuid)[5], ((uint16_t *)uuid)[6], ((uint16_t *)uuid)[7]) < 0) {
				free(uuidString);
				uuidString = NULL;
			}
			#endif
		}
	}
	
	return uuidString;
}

wchar_t *uuid_toStringW(struct uuid *uuid) {
	// C99-compatible compile-time check for the UUID4 structure's size.
	NP_GOODIES_UUID_CHECK_STRUCT_SIZE(sizeof(UUID4) != UUID_BYTE_LENGTH);
	
	wchar_t *uuidString = NULL;
	
	if(uuid != NULL) {
		uuidString = malloc(sizeof(wchar_t) * (UUID_CHAR_COUNT + 1));
		
		if(uuidString != NULL) {
			#if defined(NP_GOODIES_ADD_C11_OPTIMIZATIONS) && defined(NP_STDC_C11)
			if(swprintf_s(uuidString, UUID_CHAR_COUNT + 1, L"%08X-%04X-%04X-%04X-%04X%04X%04X",
						  ((uint32_t *)uuid)[0], ((uint16_t *)uuid)[2], ((uint16_t *)uuid)[3], ((uint16_t *)uuid)[4],
						  ((uint16_t *)uuid)[5], ((uint16_t *)uuid)[6], ((uint16_t *)uuid)[7]) < 0) {
				free(uuidString);
				uuidString = NULL;
			}
			#else
			if(swprintf(uuidString, UUID_CHAR_COUNT + 1, L"%08X-%04X-%04X-%04X-%04X%04X%04X",
						((uint32_t *)uuid)[0], ((uint16_t *)uuid)[2], ((uint16_t *)uuid)[3], ((uint16_t *)uuid)[4],
						((uint16_t *)uuid)[5], ((uint16_t *)uuid)[6], ((uint16_t *)uuid)[7]) < 0) {
				free(uuidString);
				uuidString = NULL;
			}
			#endif
		}
	}
	
	return uuidString;
}

/** @} */ // end of group_uuid
