@echo off

:: These variables should point to '.exe' files.
set MSVC_DUMPBIN="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\bin\Hostx64\x64\dumpbin.exe"
set MSVC_LIB="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\bin\Hostx64\x64\lib.exe"

:: If Python cannot be found in PATH, this variable will be used instead.
:: It should also directly point to an exe file.
set PYTHON_EXE="C:\Program Files\Python312\python.exe"

exit /b
