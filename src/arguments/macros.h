/** @file */

#pragma once

#include "../text.h"

#if defined(NP_GOODIES_ARGUMENTS_USE_WCHAR)

#define np_args_L(str) L##str

#define np_args_char wchar_t

#define np_args_strlen wcslen
#define np_args_strcmp wcscmp

#define np_args_areStringsEqual text_areStringsEqualW
#define np_args_copyString text_copyW
#define np_args_stringStartsWith text_startsWithW
#define np_args_isStringEmpty text_isEmptyW
#define np_args_nextSpaceIndex text_nextSpaceIndexW

#define np_args_error_println error_wprintln
#define np_args_trace_println trace_wprintln

#else

#define np_args_L(str) str

#define np_args_char char

#define np_args_strlen strlen
#define np_args_strcmp strcmp

#define np_args_areStringsEqual text_areStringsEqual
#define np_args_copyString text_copy
#define np_args_stringStartsWith text_startsWith
#define np_args_isStringEmpty text_isEmpty
#define np_args_nextSpaceIndex text_nextSpaceIndex

#define np_args_error_println error_println
#define np_args_trace_println trace_println

#endif
