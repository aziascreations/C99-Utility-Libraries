#include <stdio.h>
#include <string.h>

#include "../src/hash/crc32/crc32.h"

static char *testString1 = "123456789";
static char *testString2 = "The quick brown fox jumps over the lazy dog";

int main() {
	printf("CRC32B:\n");

	// See:
	// * https://crccalc.com/
	// * 7Zip CRC32(B) hashing

	// Expected: CBF43926
	printf("> 0x%08x <= '%s' (%zu)\n", hash_crc32b(testString1, strlen(testString1)), testString1, strlen(testString1));

	// Expected: 414FA339
	printf("> 0x%08x <= '%s' (%zu)\n", hash_crc32b(testString2, strlen(testString2)), testString2, strlen(testString2));

	return 0;
}
