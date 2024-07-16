@echo off
setlocal

:: NEVER CALL THIS SCRIPT DIRECTLY !!!
:: USE THE 'build-msvc.cmd' ONE INSTEAD !!!

:: Grabbing launch arguments into distinct variables and removing the double quotes
echo Retrieving launch arguments
set _VCVARS_BATCH=%1
set _VCVARS_BATCH=%_VCVARS_BATCH:"=%
set _BUILD_DIR=%2
set _BUILD_DIR=%_BUILD_DIR:"=%
set _SRC_DIR=%3
set _SRC_DIR=%_SRC_DIR:"=%
set _BENCHMARK_DIR=%4
set _BENCHMARK_DIR=%_BENCHMARK_DIR:"=%
set _EXAMPLES_DIR=%5
set _EXAMPLES_DIR=%_EXAMPLES_DIR:"=%
set _RSC_DIR=%6
set _RSC_DIR=%_RSC_DIR:"=%
set _CC_FLAGS=%7
set _CC_FLAGS=%_CC_FLAGS:"=%
set _LINK_FLAGS=%8
set _LINK_FLAGS=%_LINK_FLAGS:"=%
echo ^> _VCVARS_BATCH=%_VCVARS_BATCH%
echo ^> _BUILD_DIR=%_BUILD_DIR%
echo ^> _SRC_DIR=%_SRC_DIR%
echo ^> _BENCHMARK_DIR=%_BENCHMARK_DIR%
echo ^> _EXAMPLES_DIR=%_EXAMPLES_DIR%
echo ^> _RSC_DIR=%_RSC_DIR%
echo ^> _CC_FLAGS=%_CC_FLAGS%
echo ^> _LINK_FLAGS=%_LINK_FLAGS%

:: Calling the given VS script to get 'CL' and 'LINK' in the PATH
echo Setting up VS environment
call "%_VCVARS_BATCH%" > nul

:: Preliminary checks
echo Checking the PATH
where /q cl
IF ERRORLEVEL 1 (
    echo ^> Unable to find 'cl.exe'
    goto end
)
echo ^> Found 'cl.exe'
where /q link
IF ERRORLEVEL 1 (
    echo ^> Unable to find 'link.exe'
    goto end
)
echo ^> Found 'link.exe'
where /q rc
IF ERRORLEVEL 1 (
    echo ^> Unable to find 'rc.exe'
    goto end
)
echo ^> Found 'rc.exe'

:: Compiling our library and everything else
echo Preparing build directory
rmdir /Q /S "%_BUILD_DIR%" 2> nul > nul
mkdir "%_BUILD_DIR%"
echo ^> Created '%_BUILD_DIR%' !

:: Going into the script's directory
pushd "%_BUILD_DIR%"

:: Getting other variables here since we couldn't before
echo Setting up even more variables and directories
set _BIN_DIR=%CD%\bin
set _OBJ_DIR=%CD%\obj
echo _BIN_DIR=%_BIN_DIR%
echo _OBJ_DIR=%_OBJ_DIR%
mkdir %_BIN_DIR%
mkdir %_OBJ_DIR%

:: Compiling the DLL
echo Library ^> UCRT DLL Dynamic
mkdir %_BIN_DIR%\dll_dynamic
mkdir %_OBJ_DIR%\dll_dynamic
mkdir %_OBJ_DIR%\dll_dynamic\arguments
mkdir %_OBJ_DIR%\dll_dynamic\hash
mkdir %_OBJ_DIR%\dll_dynamic\hash\crc32
mkdir %_OBJ_DIR%\dll_dynamic\hashmaps
mkdir %_OBJ_DIR%\dll_dynamic\hashmaps\chained
mkdir %_OBJ_DIR%\dll_dynamic\hashmaps\open
mkdir %_OBJ_DIR%\dll_dynamic\lists
mkdir %_OBJ_DIR%\dll_dynamic\lists\double
mkdir %_OBJ_DIR%\dll_dynamic\lists\single
mkdir %_OBJ_DIR%\dll_dynamic\uuid
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\arguments\arguments.o" -c "%_SRC_DIR%\arguments\arguments.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\arguments\help.o" -c "%_SRC_DIR%\arguments\help.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\hash\crc32\crc32.o" -c "%_SRC_DIR%\hash\crc32\crc32.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\hashmaps\chained\hashmap.o" -c "%_SRC_DIR%\hashmaps\chained\hashmap.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\hashmaps\utils.o" -c "%_SRC_DIR%\hashmaps\utils.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\lists\double\dllist.o" -c "%_SRC_DIR%\lists\double\dllist.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\lists\single\sllist.o" -c "%_SRC_DIR%\lists\single\sllist.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\lists\commons.o" -c "%_SRC_DIR%\lists\commons.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\uuid\uuid.o" -c "%_SRC_DIR%\uuid\uuid.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\uuid\uuid4.o" -c "%_SRC_DIR%\uuid\uuid4.c"
cl %_CC_FLAGS% /DNP_GOODIES_EXPORT_ALL /Fo: "%_OBJ_DIR%\dll_dynamic\text.o" -c "%_SRC_DIR%\text.c"
rc /nologo /fo "%_OBJ_DIR%\dll_dynamic\np_clang_goodies.res" "%_RSC_DIR%\np_clang_goodies.rc"
set _DLL_OBJS=
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\arguments\arguments.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\arguments\help.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\hash\crc32\crc32.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\hashmaps\chained\hashmap.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\hashmaps\utils.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\lists\double\dllist.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\lists\single\sllist.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\lists\commons.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\uuid\uuid.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\uuid\uuid4.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\text.o"
set _DLL_OBJS=%_DLL_OBJS% "%_OBJ_DIR%\dll_dynamic\np_clang_goodies.res"
link %_LINK_FLAGS% /DLL %_DLL_OBJS% /out:%_BIN_DIR%\dll_dynamic\np_clang_goodies.dll


echo Benchmarks
echo Benchmark ^> CRC32 Implementations
cl %_CC_FLAGS% /Fo: "%_OBJ_DIR%\bm_crc32_implementations.o" -c "%_BENCHMARK_DIR%\bm_crc32_implementations.c"
link %_LINK_FLAGS% "%_OBJ_DIR%\bm_crc32_implementations.o" /out:%_BIN_DIR%\bm_crc32_implementations.exe
echo Benchmark ^> Binary Powers
cl %_CC_FLAGS% /Fo: "%_OBJ_DIR%\bm_powers_of_two.o" -c "%_BENCHMARK_DIR%\bm_powers_of_two.c"
link %_LINK_FLAGS% "%_OBJ_DIR%\bm_powers_of_two.o" /out:%_BIN_DIR%\bm_powers_of_two.exe
echo Benchmark ^> Binary Roots
cl %_CC_FLAGS% /Fo: "%_OBJ_DIR%\bm_square_of_two_mask.o" -c "%_BENCHMARK_DIR%\bm_square_of_two_mask.c"
link %_LINK_FLAGS% "%_OBJ_DIR%\bm_square_of_two_mask.o" /out:%_BIN_DIR%\bm_square_of_two_mask.exe


:: Going back to the original directory
:end-context
popd

:: Letting the user check the logs
:end
endlocal
exit /b
