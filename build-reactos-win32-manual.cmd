@echo off
setlocal enabledelayedexpansion

:: Going into the script's directory
pushd %~dp0

:: Preparing TCC
set TCC="..\.bin\tcc.exe"

:: Removing old build folders
echo.
echo Removing old folders
echo --------------------
rmdir cmake-build-reactos-tcc-manual /s /q 2> nul
echo Done :)

:: Compiling
echo.
echo Compiling some tests
echo --------------------
mkdir cmake-build-reactos-tcc-manual
cd cmake-build-reactos-tcc-manual
mkdir lib

echo ^> Copying '.def' files...
copy ..\rsc\*.def lib\ > nul
echo.

:: TODO: Automate this
echo ^> Listing '.c' files...
set NP_C99_GOODIES_C_FILES=
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/arguments/arguments.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/arguments/help.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/hash/crc32/crc32.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/hashmaps/utils.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/hashmaps/chained/hashmap.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/lists/commons.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/lists/single/sllist.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/lists/double/dllist.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/uuid/uuid.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/uuid/uuid4.c
set NP_C99_GOODIES_C_FILES=%NP_C99_GOODIES_C_FILES% ../src/text.c
echo ^> %NP_C99_GOODIES_C_FILES%
echo.

:: TODO: Add input lib switches
echo ^> Compiling 'np_clang_goodies.dll'...
%TCC% -m64 -DNP_GOODIES_EXPORT_ALL -o np_clang_goodies.dll -shared %NP_C99_GOODIES_C_FILES%
echo.

if not exist "np_clang_goodies.def" (
	echo ^> Creating missing 'np_clang_goodies.def'...
	%TCC% -impdef np_clang_goodies.dll
	echo.
)

echo ^> Moving 'np_clang_goodies.def' into 'lib/'...
move np_clang_goodies.def lib\ > nul
echo.

echo ^> Moving final test executables...
%TCC% -m64 -o test_platform_x64.exe -std=c99 -x c ../tests/misc/test_platform.c
%TCC% -m64 -o bm_crc32_implementations_x64.exe -std=c99 -x c ../benchmarks/bm_crc32_implementations.c
:: The 'uuid_win32_x64' still crashes, the callback might be broken :/
%TCC% -m64 -Llib -lcrypt32 -lnp_clang_goodies -o uuid_win32_x64.exe -std=c99 -x c ../examples/uuid_win32.c

cd ..
echo Done :)

:: Going back to the original directory
popd

:: Letting the user check the logs
echo.
endlocal
pause
