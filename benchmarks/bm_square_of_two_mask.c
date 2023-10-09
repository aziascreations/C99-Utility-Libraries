#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Doing 100M tests
#define TEST_COUNT 100000000

int main() {
	printf("Benchmarking bitwise masking for powers of two with '%%' and '&'...\n");
	
	// This value helps in preventing removal of zero-code like those benchmarks.
	int zcp = 0;
	
	int i;
	clock_t c_start;
	clock_t c_end;
	clock_t time_modulo;
	clock_t time_bit_and;
	
	printf("Testing '%%' with random values...\n");
	srand(42);
	c_start = clock();
	for(i = 0; i < TEST_COUNT; i++) {
		zcp &= (rand() % 0x0FFF);
	}
	c_end = clock();
	time_modulo = c_end - c_start;
	
	printf("Testing '&' with random values...\n");
	srand(42);
	c_start = clock();
	for(i = 0; i < TEST_COUNT; i++) {
		// FIXME: Gets optimized out for some reason...
		zcp &= (rand() & 0x0FFF);
	}
	c_end = clock();
	time_bit_and = c_end - c_start;
	
	printf("Results:\n");
	printf("> Iterations: %d\n", TEST_COUNT);
	printf("> Modulo: %ldms\n", time_modulo);
	printf("> Bitwise: %ldms\n", time_bit_and);
	
	// Making suze `zcp` isn't optimized out, and therefore, taking out our benchmark with it.
	printf("> Trash Value: %d\n", zcp);
}
