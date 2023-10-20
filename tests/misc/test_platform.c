#include "stdbool.h"
#include "stdio.h"

#include "../assert.h"

#include "../../src/platform.h"

int main() {
    printf("Operating System:\n");
    #ifdef NP_OS_WINDOWS
    printf("> Windows\n");
    #endif
	#ifdef NP_OS_LINUX
	printf("> Linux\n");
	#endif
	#ifdef NP_OS_UNIX
	printf("> Unix\n");
	#endif
    #ifdef NP_OS_CYGWIN
    printf("> Cygwin\n");
    #endif
    #ifdef NP_OS_UNKNOWN
    printf("> Unknown\n");
    #endif

    printf("Compiler:\n");
    #ifdef NP_COMPILER_MSVC
    printf("> MSVC\n");
    #endif
    #ifdef NP_COMPILER_GNUC
    printf("> GNUC\n");
    #endif
	#ifdef NP_COMPILER_CLANG
	printf("> CLANG\n");
	#endif
	#ifdef NP_COMPILER_MINGW
	printf("> MINGW\n");
	#endif
	#ifdef NP_COMPILER_TCC
	printf("> TCC\n");
	#endif
    #ifdef NP_COMPILER_UNKNOWN
    printf("> Unknown\n");
    #endif

    printf("CPU Architecture:\n");
    #ifdef NP_ARCH_x64
    printf("> x64\n");
    #endif
    #ifdef NP_ARCH_x86
    printf("> x86\n");
    #endif
    #ifdef NP_ARCH_ARM
    printf("> ARM\n");
    #endif
	#ifdef NP_ARCH_ARM_GENERIC
	printf("> ARM (Generic)\n");
	#endif
    #ifdef NP_ARCH_ARMv8
    printf("> ARMv8\n");
    #endif
    #ifdef NP_ARCH_AARCH64
    printf("> AARCH64\n");
    #endif
    #ifdef NP_ARCH_UNKNOWN
    printf("> Unknown\n");
	#endif
	
	printf("Language Standards (C):\n");
    #ifdef NP_STDC_C89
    printf("> C89\n");
    #endif
    #ifdef NP_STDC_C90
    printf("> C90\n");
    #endif
    #ifdef NP_STDC_C99
    printf("> C99\n");
    #endif
    #ifdef NP_STDC_C11
    printf("> C11\n");
    #endif
    #ifdef NP_STDC_C18
    printf("> C18\n");
    #endif

    printf("Result:\n");
    #ifdef NP_OS_UNKNOWN
    assert(false, "Unknown OS !")
    #endif
    #ifdef NP_COMPILER_UNKNOWN
    assert(false, "Unknown Compiler !")
    #endif
    #ifdef NP_ARCH_UNKNOWN
    assert(false, "Unknown CPU architecture !")
    #endif
    #ifdef NP_STDC_UNKNOWN
    assert(false, "Unknown C language standard !")
    #endif
    assert(true, "Detected a known and valid configuration :)")

    return 0;
}
