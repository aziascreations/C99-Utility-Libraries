@echo off
setlocal

pushd %CD%
cd /D "%~dp0"

call "%~dp0\0_config.cmd"

echo Checking the PATH
IF NOT EXIST %MSVC_DUMPBIN% (
    echo ^> Unable to find 'dumpbin.exe' as indicated in '%%MSVC_DUMPBIN%%' !
    echo ^> Please check the '0_config.cmd' script !
    goto end
)
echo ^> Found 'dumpbin.exe' at the given location !

echo Removing old '.exp' files from 'libs/'...
del /S /Q .\libs\*.exp 2> nul

echo Iterating over all '.dll' files in 'libs/'...
for /R ".\libs\" %%i in (*.dll) do call :sub-dump-exp %%i

echo Done !

:end
popd
endlocal
pause
exit /b


:sub-dump-exp
echo ^> %1
pushd %~dp1
%MSVC_DUMPBIN% /nologo /exports "%~nx1" > "%~n1.exp"
popd
exit /b
