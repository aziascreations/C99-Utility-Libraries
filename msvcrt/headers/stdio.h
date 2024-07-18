#pragma once

//#include <stddef.h>

//#warning "Test123"

// https://windows10dll.nirsoft.net/msvcrt_dll.html

//// Dirty hack to get MSVCRT support in the final DLL
//#if defined(NP_GOODIES_BUILD_WIN32_NODEFAULTLIB) && defined(NP_OS_WINDOWS)
//#define printf _cprintf
//#endif

//#define printf _cprintf

// #define printf _cprintf
// /Dprintf=_cprintf
// /ALTERNATENAME:printf=_cprintf
// https://github.com/microsoft/STL/issues/2655
// https://hero.handmade.network/forums/code-discussion/t/94-guide_-_how_to_avoid_c_c++_runtime_on_windows

// https://learn.microsoft.com/en-us/cpp/build/reference/external-external-headers-diagnostics?view=msvc-170

//UUID, source of issues
// Dirty hack to get MSVCRT support in the final DLL
//#if defined(NP_GOODIES_BUILD_WIN32_NODEFAULTLIB) && defined(NP_OS_WINDOWS)
////#define swprintf _cprintf
//#else
//#include <stdio.h>
//#endif


__declspec(dllimport) int printf(
    const char *__format, ...);

__declspec(dllimport) int sprintf(
    char *__stream,
    const char *__format, ...);

// Causes redefinition issues, IDK how...
//__declspec(dllimport) int swprintf(
//    wchar_t* const _Buffer,
//    size_t const _BufferCount,
//    wchar_t const* const _Format,
//    ...);
