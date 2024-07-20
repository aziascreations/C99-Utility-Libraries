@echo off
setlocal

echo NibblePoker's C99 Goodies MSVC Build
echo ========================================


:: You can edit these variables to fit your environment and desired build
set BUILD_DIR=%~dp0\build-msvc
set VCVARS_ROOT=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build

set FLAGS_CC=/nologo /Ot /Gy /Oy /TC /GS- /Gs9999999 /MD
set FLAGS_LINK=/nologo /emittoolversioninfo:no /emitpogophaseinfo /MANIFEST:EMBED

set FLAGS_MSVCRT_CC=%FLAGS_CC%
set FLAGS_MSVCRT_LINK=%FLAGS_LINK%

:: Notes
:: /emittoolversioninfo:no => Undocumented, Removes Rich PE stuff
:: /emitpogophaseinfo      => Undocumented, MAY remove debug data from .pdata section

:: Stuff you don't have to touch
set BENCHMARK_DIR=%~dp0\benchmarks
set EXAMPLES_DIR=%~dp0\examples
set SRC_DIR=%~dp0\src
set RSC_DIR=%~dp0\rsc
set MSVCRT_HEADER_DIR=%~dp0\msvcrt\headers
set MSVCRT_LIB_DIR=%~dp0\msvcrt\libs


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
                             "%FLAGS_LINK% notelemetry.obj" ^
                             "%FLAGS_LINK% notelemetry.obj"
echo.

:build-x64-msvcrt
::/DNP_GOODIES_BUILD_WIN32_NODEFAULTLIB
echo C99 Goodies - x64 MSVCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars64.bat" "%BUILD_DIR%\x64-msvcrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_MSVCRT_CC% /external:W4 /external:I ""%MSVCRT_HEADER_DIR%""" ^
                             "%FLAGS_MSVCRT_LINK% /ENTRY:DllMain /NODEFAULTLIB notelemetry.obj user32.lib kernel32.lib ""%MSVCRT_LIB_DIR%\x64\win11-23h2-pro_msdn-iso\System32\msvcrt.lib""" ^
                             "%FLAGS_MSVCRT_LINK% /ENTRY:main /NODEFAULTLIB notelemetry.obj user32.lib kernel32.lib ""%MSVCRT_LIB_DIR%\x64\win11-23h2-pro_msdn-iso\System32\msvcrt.lib"""
echo.

:build-x86-ucrt
echo C99 Goodies - x86 UCRT Build
echo ========================================
call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars32.bat" "%BUILD_DIR%\x86-ucrt" "%SRC_DIR%" ^
                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
                             "%FLAGS_CC%" ^
                             "%FLAGS_LINK% notelemetry.obj" ^
                             "%FLAGS_LINK% notelemetry.obj"
echo.

:: I can't figure out the __allmul issue right now, I'll handle it later
:::build-x86-msvcrt
::echo C99 Goodies - x86 MSVCRT Build
::echo ========================================
::call build-msvc-internal.cmd "%VCVARS_ROOT%\vcvars32.bat" "%BUILD_DIR%\x86-msvcrt" "%SRC_DIR%" ^
::                             "%BENCHMARK_DIR%" "%EXAMPLES_DIR%" "%RSC_DIR%" ^
::                             "%FLAGS_MSVCRT_CC% /external:W4 /external:I ""%MSVCRT_HEADER_DIR%""" ^
::                             "%FLAGS_MSVCRT_LINK% /ENTRY:DllMain /ALTERNATENAME:__allmul=_allmul /NODEFAULTLIB notelemetry.obj user32.lib kernel32.lib ""%MSVCRT_LIB_DIR%\x86\win11-23h2-pro_msdn-iso_x64\SysWOW64\msvcrt.lib""" ^
::                             "%FLAGS_MSVCRT_LINK% /ENTRY:main /ALTERNATENAME:__allmul=_allmul /NODEFAULTLIB notelemetry.obj user32.lib kernel32.lib ""%MSVCRT_LIB_DIR%\x86\win11-23h2-pro_msdn-iso_x64\SysWOW64\ntdll.lib"" ""%MSVCRT_LIB_DIR%\x86\win11-23h2-pro_msdn-iso_x64\SysWOW64\msvcrt.lib"""
:::: _ftlused => https://yal.cc/cpp-a-very-tiny-dll/
:::: ___allmul => _allmul => ntdll.lib => Could that work: https://github.com/microsoft/STL/issues/2655
::echo.


:: Letting the user check the logs
:end
endlocal
pause
