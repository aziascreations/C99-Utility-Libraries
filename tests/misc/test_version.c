#include <stdio.h>

#include "../assert.h"

#include "../../src/debug.h"
#include "../../src/version.h"

int main(void) {
	// Testing components
	debug_println("> Major: %d", NP_CLANG_GOODIES_VERSION_MAJOR);
	debug_println("> Minor: %d", NP_CLANG_GOODIES_VERSION_MINOR);
	debug_println("> Patch: %d", NP_CLANG_GOODIES_VERSION_PATCH);
	debug_println("> Extra: %d", NP_CLANG_GOODIES_VERSION_EXTRA);
	
	assert(NP_CLANG_GOODIES_VERSION_MAJOR == NP_GOODIES_VERSION_MAJOR, "Version's major is numerical and correct.")
	assert(NP_CLANG_GOODIES_VERSION_MINOR == NP_GOODIES_VERSION_MINOR, "Version's minor is numerical and correct.")
	assert(NP_CLANG_GOODIES_VERSION_PATCH == NP_GOODIES_VERSION_PATCH, "Version's patch is numerical and correct.")
	assert(NP_CLANG_GOODIES_VERSION_EXTRA == NP_GOODIES_VERSION_EXTRA, "Version's extra is numerical and correct.")
	
	// Testing components
	debug_println("> Version Semver: %s", NP_CLANG_GOODIES_VERSION);
	debug_println("> Version Semver: %s", NP_CLANG_GOODIES_VERSION);
	
	return 0;
}
