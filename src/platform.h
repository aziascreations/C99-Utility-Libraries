#pragma once

// See: https://sourceforge.net/p/predef/wiki/OperatingSystems/
// Others: __APPLE__, __FreeBSD__, __NetBSD__, __OpenBSD__, __sun, _AIX, __HAIKU__, __ANDROID__

#if defined(_WIN32) || defined(_WIN64)
    #define NP_OS_WIN
#elif defined(__linux__)
    #define NP_OS_UNIX
    #define NP_OS_LINUX
#elif defined(__CYGWIN__)
    #define NP_OS_CYGWIN
#else
    #define NP_OS_UNKNOWN
    #warning Unknown OS !
#endif


// See: https://sourceforge.net/p/predef/wiki/Compilers/
// Others: __TINYC__, __TURBOC__, __BORLANDC__, __LCC__, __llvm__

#if defined(_MSC_VER)
    // Untested !
    #define NP_COMPILER_MSVC
#elif defined(__clang__)
    #define NP_COMPILER_CLANG
#elif defined(__GNUC__)
    // Works in GCC & Clang
    #define NP_COMPILER_GNUC
#elif defined(__MINGW32__) || defined(__MINGW64__)
    // Untested !
    #define NP_COMPILER_MINGW
#else
    #define NP_COMPILER_UNKNOWN
    #warning Unknown compiler !
#endif


// See: https://sourceforge.net/p/predef/wiki/Architectures/
// Others: ?RISC-V (Find the definition)

#if defined(__x86_64__)
    // Works in GCC & Clang on x64 machine targeting x64 machines
    #define NP_ARCH_x64
#elif defined(__i386__)
    // Untested !
    #define NP_ARCH_x86
#elif defined(__ARM_ARCH)
    // Untested !
    // TODO: Test on RPI1B+ or Orange Pi 0
    #define NP_ARCH_ARM
#elif defined(__aarch64__)
    // Untested !
    // TODO: Test on NanoPi R4S
    #define NP_ARCH_ARMv8
    #define NP_ARCH_AARCH64
#else
    #define NP_ARCH_UNKNOWN
    #warning Unknown CPU architecture !
#endif
