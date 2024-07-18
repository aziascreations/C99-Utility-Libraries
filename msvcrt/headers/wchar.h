#pragma once

#include <stddef.h>

#define WCHAR_MIN 0x0000
#define WCHAR_MAX 0xffff

#define wchar_t unsigned short

__declspec(dllimport) int swprintf(wchar_t* const _Buffer, size_t const _BufferCount, wchar_t const* const _Format, ...);
