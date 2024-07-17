@echo off

pushd %CD%
cd /D "%~dp0"

echo Removing old '.exp', '.def' and '.lib' files from 'libs/'...
del /S /Q .\libs\*.exp 2> nul
del /S /Q .\libs\*.def 2> nul
del /S /Q .\libs\*.lib 2> nul

echo Done !

:end
popd
pause
exit /b
