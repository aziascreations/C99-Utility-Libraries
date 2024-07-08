#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/uuid/uuid4.h"

bool bufferRandomFiller(void *uuidData, size_t uuidLength) {
	// Filling the UUID4 buffer with random data first.
	// Notes:
	//   * A compiler "#if" is used to optimize the random population.
	//   * However, the highest value I found for `RAND_MAX` was 0x7FFFFFFF which means it's not long enough to
	//      populate 4 bytes fully, which is therefore not fully tested, but should be working properly.
	#if RAND_MAX >= 0xFFFFFFFF
	// We can generate 4 full bytes randomly. (Untested !!!)
	for(size_t i = 0; i < (uuidLength >> 2); i++) {
		((uint32_t*) uuidData)[i] = (uint32_t) rand();
	}
	#elif RAND_MAX >= 0xFFFF
	// We can generate 2 full bytes randomly.
	for(size_t i = 0; i < (uuidLength >> 1); i++) {
		((uint16_t*) uuidData)[i] = (uint16_t) rand();
	}
	#else
	// We can generate a full byte randomly.
	for(size_t i = 0; i < uuidLength; i++) {
		((uint8_t*) uuidData)[i] = (uint8_t) rand();
	}
	#endif
	
	return true;
}

int main() {
	// Preparing the random number generator.  (This method isn't recommended)
	// You should seek out better seed sources such as `/dev/urandom` or `BCryptGenRandom`.
	srand(time(NULL));
	
	// Creating a new random UUID4.
	UUID4 *uuid4 = uuid4_generate(&bufferRandomFiller);
	
	// Converting the UUID4 to a `char` string.
	// The `uuid_toStringW` function can be used to get a `wchar_t` string.
	char *uuidStr = uuid_toStringA(uuid4);
	wchar_t *uuidStrW = uuid_toStringW(uuid4);
	
	// Printing it out.
	printf("%s\n", uuidStr);
	printf("%ls\n", uuidStrW);
	
	// Freeing resources.
	free(uuidStrW);
	free(uuidStr);
	free(uuid4);
}
