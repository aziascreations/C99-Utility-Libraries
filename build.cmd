@echo off

cd /d %~dp0

:: C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2022\Visual Studio Tools\VC
::call "D:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
::call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

rmdir build /s /q
mkdir build
cd build
cmake ..
cmake --build . --config Debug
cmake --build . --config Release
cmake --build . --config RelWithDebInfo
cmake --build . --config MinSizeRel
cd ..

pause
