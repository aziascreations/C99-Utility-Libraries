/** @file */

#if !defined(NP_ONCE_C99_GOODIES_ARGUMENTS_MACROS)
#define NP_ONCE_C99_GOODIES_ARGUMENTS_MACROS

#include "../text.h"

#if defined(NP_GOODIES_ARGUMENTS_USE_WCHAR) || defined(NP_GOODIES_ALL_USE_WCHAR)

#define np_args_L(str) L##str

#define np_args_char wchar_t

#define np_args_strlen wcslen
#define np_args_strcmp wcscmp

#define np_args_areStringsEqual text_areStringsEqualW
#define np_args_copyString text_copyW
#define np_args_stringStartsWith text_startsWithW
#define np_args_isStringEmpty text_isEmptyW
#define np_args_nextSpaceIndex text_nextSpaceIndexW

#define np_args_error_println error_printlnW
#define np_args_trace_println trace_printlnW

#else

#define np_args_L(str) str

#define np_args_char char

#define np_args_strlen strlen
#define np_args_strcmp strcmp

#define np_args_areStringsEqual text_areStringsEqualA
#define np_args_copyString text_copyA
#define np_args_stringStartsWith text_startsWithA
#define np_args_isStringEmpty text_isEmptyA
#define np_args_nextSpaceIndex text_nextSpaceIndexA

#define np_args_error_println error_printlnA
#define np_args_trace_println trace_printlnA

#endif

#endif /* !NP_ONCE_C99_GOODIES_ARGUMENTS_MACROS */
