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
    //#warning Unknown OS !
#endif


// See: https://sourceforge.net/p/predef/wiki/Compilers/
// Others: __TINYC__, __TURBOC__, __BORLANDC__, __LCC__, __llvm__

#if defined(_MSC_VER)
    #define NP_COMPILER_MSVC
#elif defined(__clang__)
    #define NP_COMPILER_CLANG
#elif defined(__GNUC__)
    #define NP_COMPILER_GNUC
#elif defined(__MINGW32__) || defined(__MINGW64__)
    // Untested !
    #define NP_COMPILER_MINGW
#else
    #define NP_COMPILER_UNKNOWN
    //#warning Unknown compiler !
#endif


// See: https://sourceforge.net/p/predef/wiki/Architectures/
// Others: ?RISC-V (Find the definition)

#if defined(__x86_64__) || defined(_M_X64)
    #define NP_ARCH_x64
#elif defined(__i386__) || defined(_M_IX86)
    // Untested !
    #define NP_ARCH_x86
#elif defined(__aarch64__)
    #define NP_ARCH_ARM
    #define NP_ARCH_ARMv8
    #define NP_ARCH_AARCH64
#elif defined(__ARM_ARCH)
    // Untested !
    // TODO: Test on RPI1B+ or Orange Pi 0
    #define NP_ARCH_ARM
    #define NP_ARCH_ARM_GENERIC
#else
    #define NP_ARCH_UNKNOWN
    //#warning Unknown CPU architecture !
#endif


// Setting the OS-specific library export macro
#if defined(NP_OS_WIN) || defined(NP_OS_CYGWIN)
    #define NP_DLL_EXPORT __declspec(dllexport)
#elif defined(NP_OS_LINUX) || defined(NP_OS_UNIX)
    #define NP_DLL_EXPORT __attribute__((visibility("default")))
#else
    #define NP_DLL_EXPORT
#endif
