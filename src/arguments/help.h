/** @file */

#if !defined(NP_ONCE_C99_GOODIES_ARGUMENTS_HELP)
#define NP_ONCE_C99_GOODIES_ARGUMENTS_HELP

#include <stdio.h>

#include "./flags.h"
#include "./structs.h"


// Unicode macros
#if defined(NP_UNICODE)
	#define args_printHelpText args_printHelpTextW
#else
	#define args_printHelpText args_printHelpTextA
#endif


bool args_printHelpTextA(VerbA *verb, char *programName, short consoleWidth);

bool args_printHelpTextW(VerbW *verb, wchar_t *programName, short consoleWidth);

#endif /* !NP_ONCE_C99_GOODIES_ARGUMENTS_HELP */
