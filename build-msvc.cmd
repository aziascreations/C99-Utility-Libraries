@echo off
setlocal

echo NibblePoker's C99 Goodies MSVC Build
echo ========================================


:: You can edit these variables to fit your environment and desired build
set BUILD_DIR=%~dp0\build-msvc
set VCVARS_ROOT=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build

set FLAGS_CC=/nologo /Ot /Gy /Oy /TC /GS- /Gs9999999 /MD
set FLAGS_LINK=/nologo /MANIFEST:EMBED

set FLAGS_MSVCRT_CC=%FLAGS_CC%
set FLAGS_MSVCRT_LINK=%FLAGS_LINK%


:: Stuff you don't have to touch
set BENCHMARK_DIR=%~dp0\benchmarks
set EXAMPLES_DIR=%~dp0\examples
set SRC_DIR=%~dp0\src
set RSC_DIR=%~dp0\rsc
set MSVCRT_DIR=%~dp0\msvcrt\src


:: Checking the to make sure you ain't running of a VS console
echo Checking the PATH
where /q cl
IF NOT ERRORLEVEL 1 (
    echo Found 'cl.exe' in your PATH !
    echo Use a command prompt with a clean PATH !
    goto end
)
where /q link
IF NOT ERRORLEVEL 1 (
    echo Found 'link.exe' in your PATH !
    echo Use a command prompt with a clean PATH !
    goto end
)
where /q rc
IF NOT ERRORLEVEL 1 (
    echo Found 'rc.exe' in your PATH !
    echo Use a command prompt with a clean PATH !
    goto end
)
echo ^> The PATH appears to be clean


:: Preparing the build folder
echo Preparing build directory
rmdir /Q /S %BUILD_DIR% 2> nul > nul
mkdir %BUILD_DIR%
echo ^> Created '%BUILD_DIR%' !
echo.


:: Calling the building script with distinct variable contexts
:build-x64-ucrt
echo C99 Goodies - x64 UCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars64.bat" "%BUILD_DIR%\x64-ucrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_CC%" ^
                             "%FLAGS_LINK%"
echo.

:build-x64-msvcrt
::/DNP_GOODIES_BUILD_WIN32_NODEFAULTLIB
echo C99 Goodies - x64 MSVCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars64.bat" "%BUILD_DIR%\x64-msvcrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_MSVCRT_CC% /external:W4 /external:I ""%MSVCRT_DIR%""" ^
                             "%FLAGS_MSVCRT_LINK% /NODEFAULTLIB user32.lib kernel32.lib ^"%RSC_DIR%\libs\x64\msvcrt.lib^""
echo.

:build-x86-ucrt
echo C99 Goodies - x86 UCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars32.bat" "%BUILD_DIR%\x86-ucrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_CC%" ^
                             "%FLAGS_LINK%"
echo.

:build-x86-msvcrt
echo C99 Goodies - x86 MSVCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars32.bat" "%BUILD_DIR%\x86-msvcrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_MSVCRT_CC% /external:W4 /external:I ""%MSVCRT_DIR%""" ^
                             "%FLAGS_MSVCRT_LINK% /NODEFAULTLIB user32.lib kernel32.lib ^"%RSC_DIR%\libs\x86\msvcrt.lib^""
echo.


:: Letting the user check the logs
:end
endlocal
pause
