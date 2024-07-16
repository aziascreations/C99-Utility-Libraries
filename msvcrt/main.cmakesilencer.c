#include <windows.h>

/**
 * This `DllMain` function is just here to make shut Cmake up about "unknown linker language" errors.
 * This won't affect any usage of the headers in this directory and its sub-directories.
 */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}
