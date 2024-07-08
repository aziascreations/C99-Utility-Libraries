//#pragma comment(lib, "crypt32.lib")

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <wincrypt.h>

#include "../src/uuid/uuid4.h"

bool win32RandomFiller(void *uuidData, size_t uuidLength) {
	HCRYPTPROV hCryptProv;
	
	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
		return false;
	}
	
	if(!CryptGenRandom(hCryptProv, uuidLength, uuidData)) {
		CryptReleaseContext(hCryptProv, 0);
		return false;
	}
	
	CryptReleaseContext(hCryptProv, 0);
	
	return true;
}

int main() {
	// Creating a new random UUID4.
	UUID4 *uuid4 = uuid4_generate(&win32RandomFiller);
	
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
