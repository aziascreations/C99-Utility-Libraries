@echo off

:: Going into the script's directory
pushd %~dp0

:: Preparing the build folder
rmdir cmake-build-reactos-tcc /s /q
mkdir cmake-build-reactos-tcc

:: ...
cd cmake-build-reactos-tcc

:: ???
cmake -D CMAKE_C_COMPILER=tcc ..

:: ???
cmake --build . --config Release

:: Going back to the original directory
popd

:: Letting the user check the logs
pause
