#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Doing 100M tests
#define TEST_COUNT 100000000

int main() {
	printf("Benchmarking powers of two calculation with bit shifts vs pow() ...\n");
	
	// This value helps in preventing removal of zero-code like those benchmarks.
	int zcp = 0;
	
	int i;
	clock_t c_start;
	clock_t c_end;
	clock_t time_bit_shift;
	clock_t time_pow;
	
	printf("> Testing with bit shifts...\n");
	srand(42);
	c_start = clock();
	for(i = 0; i < TEST_COUNT; i++) {
		// Same as 2^x where x = [0;7]
		zcp &= (2 << ((rand() & 0x08) - 1));
	}
	c_end = clock();
	time_bit_shift = c_end - c_start;
	
	printf("> Testing with pow()...\n");
	srand(42);
	c_start = clock();
	for(i = 0; i < TEST_COUNT; i++) {
		// Same as 2^x where x = [0;7]
		zcp &= (int) pow(2, (rand() & 0x08));
	}
	c_end = clock();
	time_pow = c_end - c_start;
	
	printf("Results:\n");
	printf("> Iterations: %d\n", TEST_COUNT);
	printf("> Bitwise: %ld ms\n", time_bit_shift);
	printf("> Pow():   %ld ms\n", time_pow);
	
	// Making suze `zcp` isn't optimized out, and therefore, taking out our benchmark with it.
	printf("> Trash Value: %d\n", zcp);
}
