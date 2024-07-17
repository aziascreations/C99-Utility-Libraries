@echo off
setlocal

pushd %CD%
cd /D "%~dp0"

call "%~dp0\0_config.cmd"

echo Checking the PATH
where /q python
IF NOT ERRORLEVEL 1 (
    echo ^> Found 'python.exe' in PATH !
    set PYTHON_EXE=python
    goto end-path-check
)
echo ^> Couldn't find 'python.exe' in PATH !
IF NOT EXIST %PYTHON_EXE% (
    echo ^> Unable to find 'python.exe' as indicated in '%%PYTHON_EXE%%' !
    echo ^> Please check the '0_config.cmd' script !
    goto end
)
:end-path-check

echo Removing old '.def' files from 'libs/'...
del /S /Q .\libs\*.def 2> nul

::echo Removing old '.def' and '.raw.def' files from 'libs/'...
::del /S /Q .\libs\*.def 2> nul
::del /S /Q .\libs\*.raw.def 2> nul

echo Iterating over all '.exp' files in 'libs/'...
for /R ".\libs\" %%i in (*.exp) do call :sub-idk %%i

echo Done !

:end
popd
endlocal
pause
exit /b


:sub-idk
echo ^> %1
pushd %~dp1
:: This solution was chosen over the 'awk' call due to the fact those often miss lines and
::  can be quite annoying to run on Windows machines.
%PYTHON_EXE% "%~dp0\exp_to_def.py" "./%~nx1" "./%~n1.def"
popd
exit /b
