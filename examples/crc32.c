#include <stdio.h>
#include <string.h>

#include "../src/hash/crc32/crc32.h"

static char* testString1 = "";
static char* testString2 = "123456789";
static char* testString3 = "The quick brown fox jumps over the lazy dog";

int main() {
	printf("CRC32B:\n");
	
	// See:
	// * https://crccalc.com/
	// * 7Zip CRC32(B) hashing
	
	// CBF43926
	printf("> 0x%08x <= '%s' (%llu)\n", hash_crc32b(testString2, strlen(testString2)), testString2, strlen(testString2));
	
	// 414FA339
	printf("> 0x%08x <= '%s' (%llu)\n", hash_crc32b(testString3, strlen(testString3)), testString3, strlen(testString3));
	
	return 0;
}
