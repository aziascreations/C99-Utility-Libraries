@echo off
setlocal enabledelayedexpansion

:: Preparing some variables
echo.
echo Preparing MSVC
echo --------------

set NP_MSVC_LOCATION=D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\
if exist "%NP_MSVC_LOCATION%" (
	echo ^> Location: "%NP_MSVC_LOCATION%"
) else (
	echo ^> Cannot find it in : "%NP_MSVC_LOCATION%"
	goto end
)

if exist "%NP_MSVC_LOCATION%\vcvars64.bat" (
	set NP_MSVC_x64="D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
	echo ^> Found the x64 script.
) else (
	echo ^> Unable to find x64 script !
)

if exist "%NP_MSVC_LOCATION%\vcvarsamd64_x86.bat" (
	set NP_MSVC_x86="D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
	echo ^> Found the amd64_x86 script.
) else (
	echo ^> Unable to find amd64_x86 script !
)

:: Doesn't work properly yet !
::if exist "%NP_MSVC_LOCATION%\vcvarsamd64_arm.bat" (
::	set NP_MSVC_arm="D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsamd64_arm.bat"
::	echo ^> Found the amd64_arm script.
::) else (
::	echo ^> Unable to find amd64_arm script !
::)

if exist "%NP_MSVC_LOCATION%\vcvarsamd64_arm64.bat" (
	set NP_MSVC_arm64="D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsamd64_arm64.bat"
	echo ^> Found the amd64_arm64 script.
) else (
	echo ^> Unable to find amd64_arm64 script !
)

:: Going into the script's directory
pushd %~dp0
rmdir cmake-build-win32-msvc-x64 /s /q 2> nul
rmdir cmake-build-win32-msvc-x86 /s /q 2> nul
rmdir cmake-build-win32-msvc-arm /s /q 2> nul
rmdir cmake-build-win32-msvc-arm64 /s /q 2> nul

:: Doing x64 build
if defined NP_MSVC_x64 (
	echo.
	echo Building x64 target
	echo -------------------
	mkdir cmake-build-win32-msvc-x64
	call %NP_MSVC_x64%
	cd cmake-build-win32-msvc-x64
	cmake ..
	cmake --build . --config Release
	cd..
)

:: Doing x86 build
if defined NP_MSVC_x86 (
	echo.
	echo Building x86 target
	echo -------------------
	mkdir cmake-build-win32-msvc-x86
	call %NP_MSVC_x86%
	cd cmake-build-win32-msvc-x86
	cmake ..
	cmake --build . --config Release
	cd..
)

:: Doing ARM build
if defined NP_MSVC_arm (
	echo.
	echo Building arm target
	echo -------------------
	mkdir cmake-build-win32-msvc-arm
	call %NP_MSVC_arm%
	cd cmake-build-win32-msvc-arm
	cmake ..
	cmake --build . --config Release
	cd..
)

:: Doing ARM64 build
if defined NP_MSVC_arm64 (
	echo.
	echo Building arm64 target
	echo -------------------
	mkdir cmake-build-win32-msvc-arm64
	call %NP_MSVC_arm64%
	cd cmake-build-win32-msvc-arm64
	cmake ..
	cmake --build . --config Release
	cd..
)

:: Going back to the original directory
popd

:: Letting the user check the logs
:end
echo.
pause
