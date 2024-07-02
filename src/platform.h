/** @file */

#if !defined(NP_ONCE_C99_GOODIES_PLATFORM)
#define NP_ONCE_C99_GOODIES_PLATFORM

/** @defgroup group_np_platform Platforms detection
 *
 * Single header whose main purpose in is to let you easily identify which compiler, OS and ISA is being
 * targeted to potentially implement platform-specific code.
 *
 * Once included, you can check for various definitions that can help you target specific targets.
 *
 * For a complete list of scenarios and their associated definitions, check [platforms.md](../platforms.md).
 *
 * \see https://sourceforge.net/p/predef/wiki/Architectures/
 * \see https://sourceforge.net/p/predef/wiki/Compilers/
 * \see https://sourceforge.net/p/predef/wiki/OperatingSystems/
 * \see https://sourceforge.net/p/predef/wiki/Standards/
 * \see https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros
 * \see [platforms.md](../platforms.md)
 *
 * @{
 */

// See: https://sourceforge.net/p/predef/wiki/OperatingSystems/
// Others: __APPLE__, __FreeBSD__, __NetBSD__, __OpenBSD__, __sun, _AIX, __HAIKU__, __ANDROID__

#if defined(_WIN32) || defined(_WIN64)
    #define NP_OS_WINDOWS
#elif defined(__linux__)
    #define NP_OS_UNIX
    #define NP_OS_LINUX
#elif defined(__CYGWIN__)
    #define NP_OS_CYGWIN
#else
    #define NP_OS_UNKNOWN
#endif


// See: https://sourceforge.net/p/predef/wiki/Compilers/
// Others: __TINYC__, __TURBOC__, __BORLANDC__, __LCC__, __llvm__

#if defined(_MSC_VER)
    #define NP_COMPILER_MSVC
#elif defined(__MINGW32__) || defined(__MINGW64__)
	#define NP_COMPILER_MINGW
#elif defined(__clang__)
    #define NP_COMPILER_CLANG
#elif defined(__GNUC__)
    #define NP_COMPILER_GNUC
#elif defined(__TINYC__)
    #define NP_COMPILER_TCC
#else
    #define NP_COMPILER_UNKNOWN
#endif


// See: https://sourceforge.net/p/predef/wiki/Architectures/
// Others: ?RISC-V (Find the definition)

#if defined(__x86_64__) || defined(_M_X64)
    #define NP_ARCH_x64
#elif defined(__i386__) || defined(_M_IX86)
    #define NP_ARCH_x86
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define NP_ARCH_ARM
    #define NP_ARCH_ARMv8
    #define NP_ARCH_AARCH64
#elif defined(__ARM_ARCH) || defined(_M_ARM)
    // TODO: Test on Linux via RPI1B+ or Orange Pi 0
    #define NP_ARCH_ARM
    #define NP_ARCH_ARM_GENERIC
#else
    #define NP_ARCH_UNKNOWN
#endif


// See: https://sourceforge.net/p/predef/wiki/Standards/

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L)
	#define NP_STDC_C94
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
	#define NP_STDC_C99
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
	#define NP_STDC_C11
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201710L)
	#define NP_STDC_C18
#endif

#if defined(__STDC__) || defined(NP_STDC_C94)
	#define NP_STDC_C89
	#define NP_STDC_C90
#endif

#if !defined(__STDC__) && !defined(NP_STDC_C94)
	#define NP_STDC_UNKNOWN
#endif


// Small fix for MSVC if no specific standard was EXPLICITLY given to the MSVC compiler.
// See: https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros
// FIXME: Flesh out and test properly
#if defined(NP_STDC_UNKNOWN) && defined(NP_COMPILER_MSVC)
	#undef NP_STDC_UNKNOWN
	#define NP_STDC_C89
	#define NP_STDC_C90
	#define NP_STDC_C99
	#define NP_STDC_C11
#endif


// Setting the OS-specific library export macro
#if defined(NP_OS_WINDOWS) && defined(NP_COMPILER_TCC)
	#define NP_DLL_EXPORT __attribute__((dllexport))
#elif defined(NP_OS_WINDOWS) || defined(NP_OS_CYGWIN)
    #define NP_DLL_EXPORT __declspec(dllexport)
#elif defined(NP_OS_LINUX) || defined(NP_OS_UNIX)
    #define NP_DLL_EXPORT __attribute__((visibility("default")))
#else
    #define NP_DLL_EXPORT
#endif


// Never define `NP_UNICODE` manually !
#if defined(NP_UNICODE)
	#error Do not define `NP_UNICODE`, use `UNICODE` or `_UNICODE` instead !
#endif

// Checking if ascii or unicode variants should be macro'ed
#if defined(UNICODE) || defined(_UNICODE)
	#define NP_UNICODE
#else
	#undef NP_UNICODE
#endif

// Defining the TEXT() macro if not defined by Windows's headers
#if !defined(TEXT)
	#if defined(NP_UNICODE)
		#define TEXT(str) L##str
	#else
		#define TEXT(str) str
	#endif
#endif



/** @} */ // end of group_np_platform

#endif /* !NP_ONCE_C99_GOODIES_PLATFORM */
