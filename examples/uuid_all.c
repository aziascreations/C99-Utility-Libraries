#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/uuid/uuid4.h"

// Used to access the `__rdtsc()` macro.
// May not work on non-x86 platforms !
#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

int main() {
	// Preparing the random number generator.  (This method isn't recommended)
	// You should seek out better seed sources such as `/dev/urandom` or `BCryptGenRandom`.
	
	//srand(time(NULL));  // Very basic and predictable.
	srand(__rdtsc());  // Slightly better, but likely to repeat since it depends on CPU cycle count.
	
	// Creating a new random UUID4
	UUID4 *uuid4 = uuid4_generate();
	
	// Converting the UUID4 to a `char` string.
	// The `uuid_toWcharString` function can be used to get a `wchar_t` string.
	char *uuidStr = uuid_toString(uuid4);
	
	// Printing it out.
	printf("%s\n", uuidStr);
	
	// Freeing resources.
	free(uuidStr);
	free(uuid4);
}
