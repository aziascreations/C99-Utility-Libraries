# Platforms detection
This page mostly concerns the [platforms.h](src/platform.h) header.

Its main purpose in is to let you easily identify which compiler, OS and ISA is being targeted to potentially
implement platform-specific code.

**External references:**<br>
&nbsp;&nbsp;&nbsp;● https://sourceforge.net/p/predef/wiki/Architectures/<br>
&nbsp;&nbsp;&nbsp;● https://sourceforge.net/p/predef/wiki/Compilers/<br>
&nbsp;&nbsp;&nbsp;● https://sourceforge.net/p/predef/wiki/OperatingSystems/


## Compilers

### MSVC
Tested with MSVC v143 from Visual Studio Community 2022.
* `NP_COMPILER_MSVC`

### CLang
Works, but needs more testing.
* `NP_COMPILER_CLANG`

### GCC
Works, but needs more testing.
* `NP_COMPILER_GNUC`

### MinGW
Untested
* `NP_COMPILER_MINGW`

### Unknown
* `NP_COMPILER_UNKNOWN`


## Platforms & ISA

### Windows x64
Tested on Windows 11 22H2 with MSVC.
* `NP_OS_WIN`
* `NP_ARCH_x64`

### Windows x86
Untested.
* `NP_OS_WIN`
* `NP_ARCH_x86`

### Windows ARM
Untested.

### Cygwin
Untested.

### Linux x64
Tested on Kubuntu 23.10 in a VM with GCC & CLang.
* `NP_OS_UNIX`
* `NP_OS_LINUX`
* `NP_ARCH_x64`

### Linux x86
Untested.

### Linux ARMv8/AArch64/ARM64
Tested on NanoPi R4S with Armbian (23.02.2).
* `NP_OS_UNIX`
* `NP_OS_LINUX`
* `NP_ARCH_ARM`
* `NP_ARCH_ARMv8`
* `NP_ARCH_AARCH64`

### Linux ARM Generic
Untested, will be done soon.
* `NP_OS_UNIX`
* `NP_OS_LINUX`
* `NP_ARCH_ARM`
* `NP_ARCH_ARM_GENERIC`

### Unknown OS *(Apple, ReactOS, ...)*
* `NP_OS_UNKNOWN`

### Unknown ISA
* `NP_ARCH_UNKNOWN`
