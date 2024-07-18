#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Helps fix issues with missing symbol in MSVCRT builds
// Source: https://stackoverflow.com/a/1583220
#if defined(_WIN32) || defined(_WIN64)
	int _fltused = 0;
#endif

#define assert(expression, name) \
if(expression) {printf("> \033[32mPASS\033[0m -> %s\n", name);} else {printf("> \033[31mFAIL\033[0m -> %s\n", name); return 1;}


// Know test vector.  (Source: 7zip's CRC32B of a .bin file with no trailing NULL byte).
const static char *tv1_str = "The quick brown fox jumps over the lazy dog";
const static uint32_t tv1_crc = 0x414FA339;

const static size_t test_data_size = 512 * 1024 * 1024;


// Original implementation by Ayman El Didi.
// Source: https://github.com/aeldidi/crc32
uint32_t crc32_v0_for_byte(uint32_t byte) {
	const uint32_t polynomial = 0xEDB88320L;
	uint32_t       result     = byte;
	size_t         i          = 0;
	
	for (; i < 8; i++) {
		result = (result >> 1) ^ (result & 1) * polynomial;
	}
	
	return result;
}

uint32_t crc32_v0(const void *input, size_t size) {
	const uint8_t *current = input;
	uint32_t       result  = 0xFFFFFFFF;
	size_t         i       = 0;
	
	for (; i < size; i++) {
		result ^= current[i];
		result = crc32_v0_for_byte(result);
	}
	
	return ~result;
}


// Alternative implementation by Ayman El Didi.
// Source: https://github.com/aeldidi/crc32
uint32_t crc32_v1_for_byte(uint32_t byte) {
	const uint32_t polynomial = 0xEDB88320L;
	uint32_t       result     = byte;
	size_t         i          = 0;
	
	for (; i < 8; i++) {
		if (result & 1) {
			result = (result >> 1) ^ polynomial;
			continue;
		}
		result >>= 1;
	}
	
	return result;
}

uint32_t crc32_v1(const void *input, size_t size) {
	const uint8_t *current = input;
	uint32_t       result  = 0xFFFFFFFF;
	size_t         i       = 0;
	
	for (; i < size; i++) {
		result ^= current[i];
		result = crc32_v1_for_byte(result);
	}
	
	return ~result;
}


// First reduction by Herwin Bozet.
// It is the same as the original one without the function call.
// Source: https://github.com/aziascreations/C99-Utility-Libraries
uint32_t crc32_v2(const char *data, size_t data_size) {
	uint32_t crc32 = 0xFFFFFFFF;
	
	for(size_t data_offset = 0; data_offset < data_size; data_offset++) {
		crc32 ^= data[data_offset];
		
		for(size_t bit_offset = 0; bit_offset < 8; bit_offset++) {
			crc32 = (crc32 >> 1) ^ (crc32 & 1) * 0xEDB88320;
		}
	}
	
	return ~crc32;
}


const static uint32_t crc32_v3_table[256] = {
		0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
		0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
		0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
		0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
		0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
		0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
		0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
		0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
		0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
		0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
		0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
		0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
		0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
		0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
		0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
		0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
		0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
		0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
		0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
		0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
		0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
		0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
		0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
		0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
		0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
		0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
		0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
		0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
		0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
		0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
		0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
		0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

// Alternative option using a pre-computed table by Herwin Bozet.
// It is the previous one, except it uses a lookup table.
// Source: https://github.com/aziascreations/C99-Utility-Libraries
uint32_t crc32_v3(const char *data, size_t data_size) {
	uint32_t crc32 = 0xFFFFFFFF;
	
	for(size_t data_offset = 0; data_offset < data_size; data_offset++) {
		crc32 = (crc32 >> 8) ^ crc32_v3_table[(data[data_offset] ^ crc32) & 0xFF];
	}
	
	return ~crc32;
}


// Actual benchmark.
int main() {
	void *test_data;
	
	clock_t c_start, c_end;
	clock_t time_v0_long;  //, time_v0_short;
	clock_t time_v1_long;  //, time_v1_short;
	clock_t time_v2_long;  //, time_v2_short;
	clock_t time_v3_long;  //, time_v3_short;
	
	int i;
	
	
	// Validating the implementations with know a know test vector.
	printf("Sanity checks:\n");
	assert(crc32_v0(tv1_str, strlen(tv1_str)) == tv1_crc, "Original implementation")
	assert(crc32_v1(tv1_str, strlen(tv1_str)) == tv1_crc, "Original alternative implementation")
	assert(crc32_v2(tv1_str, strlen(tv1_str)) == tv1_crc, "Reduced implementation")
	assert(crc32_v3(tv1_str, strlen(tv1_str)) == tv1_crc, "Look-up implementation")
	printf("\n");
	
	
	printf("Preparing pseudo-random test data...\n");
	test_data = malloc(test_data_size);
	srand(clock());
#if RAND_MAX >= 0xFFFFFFFF
	// We can generate 4 full bytes randomly. (Untested !!!)
	for(int i = 0; i < test_data_size / 4; i++) {
		((uint32_t*) test_data)[i] = (uint32_t) rand();
	}
#elif RAND_MAX >= 0xFFFF
	// We can generate 2 full bytes randomly.
	for(int i = 0; i < test_data_size / 2; i++) {
		((uint16_t*) test_data)[i] = (uint16_t) rand();
	}
#else
	// We can generate a full byte randomly.
	for(int i = 0; i < test_data_size; i++) {
		((uint8_t*) test_data)[i] = (uint8_t) rand();
	}
#endif
	printf("\n");
	
	// All tests are done by priming it once and then timing it.
	// The final CRC is printed to prevent zero-code removal when using /On flags.
	
	printf("Testing V0...\n");
	
	printf("> Full: priming => 0x%08x\n", crc32_v0(test_data, test_data_size));
	c_start = clock();
	printf("> Full: proper  => 0x%08x\n", crc32_v0(test_data, test_data_size));
	c_end = clock();
	time_v0_long = c_end - c_start;
	printf("> Full: Took %ld ms\n", time_v0_long);
	
	printf("\n");
	
	
	printf("Testing V1...\n");
	
	printf("> Full: priming => 0x%08x\n", crc32_v1(test_data, test_data_size));
	c_start = clock();
	printf("> Full: proper  => 0x%08x\n", crc32_v1(test_data, test_data_size));
	c_end = clock();
	time_v1_long = c_end - c_start;
	printf("> Full: Took %ld ms\n", time_v1_long);
	
	printf("\n");
	
	
	printf("Testing V2...\n");
	
	printf("> Full: priming => 0x%08x\n", crc32_v2(test_data, test_data_size));
	c_start = clock();
	printf("> Full: proper  => 0x%08x\n", crc32_v2(test_data, test_data_size));
	c_end = clock();
	time_v2_long = c_end - c_start;
	printf("> Full: Took %ld ms\n", time_v2_long);
	
	printf("\n");
	
	
	printf("Testing V3...\n");
	
	printf("> Full: priming => 0x%08x\n", crc32_v3(test_data, test_data_size));
	c_start = clock();
	printf("> Full: proper  => 0x%08x\n", crc32_v3(test_data, test_data_size));
	c_end = clock();
	time_v3_long = c_end - c_start;
	printf("> Full: Took %ld ms\n", time_v3_long);
	
	printf("\n");
	
	
	printf("Results...\n");
	printf("Version;Time (ms);Hash rate (B/s);Hash rate (b/s);Hash rate (KiB/s);Hash rate (Kib/s);Hash rate (MiB/s);Hash rate (Mib/s)\n");
	printf("0;%ld;%lf;%lf;%lf;%lf;%lf;%lf\n",
		   time_v0_long,
		   (double) test_data_size / (double) time_v0_long * 1000,
		   (double) test_data_size / (double) time_v0_long * 8 * 1000,
		   (double) test_data_size / (double) time_v0_long / 1024 * 1000,
		   (double) test_data_size / (double) time_v0_long * 8 / 1024 * 1000,
		   (double) test_data_size / (double) time_v0_long / 1024 / 1024 * 1000,
		   (double) test_data_size / (double) time_v0_long * 8 / 1024 / 1024 * 1000);
	printf("1;%ld;%lf;%lf;%lf;%lf;%lf;%lf\n",
		   time_v1_long,
		   (double) test_data_size / (double) time_v1_long * 1000,
		   (double) test_data_size / (double) time_v1_long * 8 * 1000,
		   (double) test_data_size / (double) time_v1_long / 1024 * 1000,
		   (double) test_data_size / (double) time_v1_long * 8 / 1024 * 1000,
		   (double) test_data_size / (double) time_v1_long / 1024 / 1024 * 1000,
		   (double) test_data_size / (double) time_v1_long * 8 / 1024 / 1024 * 1000);
	printf("2;%ld;%lf;%lf;%lf;%lf;%lf;%lf\n",
		   time_v2_long,
		   (double) test_data_size / (double) time_v2_long * 1000,
		   (double) test_data_size / (double) time_v2_long * 8 * 1000,
		   (double) test_data_size / (double) time_v2_long / 1024 * 1000,
		   (double) test_data_size / (double) time_v2_long * 8 / 1024 * 1000,
		   (double) test_data_size / (double) time_v2_long / 1024 / 1024 * 1000,
		   (double) test_data_size / (double) time_v2_long * 8 / 1024 / 1024 * 1000);
	printf("3;%ld;%lf;%lf;%lf;%lf;%lf;%lf\n",
		   time_v3_long,
		   (double) test_data_size / (double) time_v3_long * 1000,
		   (double) test_data_size / (double) time_v3_long * 8 * 1000,
		   (double) test_data_size / (double) time_v3_long / 1024 * 1000,
		   (double) test_data_size / (double) time_v3_long * 8 / 1024 * 1000,
		   (double) test_data_size / (double) time_v3_long / 1024 / 1024 * 1000,
		   (double) test_data_size / (double) time_v3_long * 8 / 1024 / 1024 * 1000);
	printf("\n");
	
	
	printf("Clearing memory...\n");
	free(test_data);
	
	return 0;
}
