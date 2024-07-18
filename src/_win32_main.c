#include "./platform.h"

#if defined(NP_OS_WINDOWS)
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
    return TRUE;
}
#endif
