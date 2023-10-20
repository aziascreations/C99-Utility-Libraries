@echo off

:: Going into the script's directory
pushd %~dp0

:: Removing old build folders
rmdir cmake-build-reactos-tcc-x86 /s /q 2> nul
rmdir cmake-build-reactos-tcc-x64 /s /q 2> nul

:: Creating new build folders
mkdir cmake-build-reactos-tcc-x86
mkdir cmake-build-reactos-tcc-x64

:: Compiling for x86
cd cmake-build-reactos-tcc-x86
cmake -G "NMake Makefiles JOM" -D CMAKE_C_COMPILER=tcc -DCMAKE_C_FLAGS="-m32" ..
cmake --build . --config Release
cd ..

:: Compiling for x64
cd cmake-build-reactos-tcc-x64
cmake -G "NMake Makefiles JOM" -D CMAKE_C_COMPILER=tcc -DCMAKE_C_FLAGS="-m64" ..
cmake --build . --config Release
cd ..

:: Going back to the original directory
popd

:: Letting the user check the logs
pause
