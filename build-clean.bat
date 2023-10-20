@echo off

:: Going into the script's directory
pushd %~dp0

:: Removing old build folders
echo.
echo Removing old build folders
echo --------------------------
for /d %%d in (cmake-build-*) do (
    if exist "%%d" (
        echo ^> Deleting "%%d"...
        rmdir /s /q "%%d"
    )
)
rmdir /s /q .\build 2> nul
echo ^> Done :)

:: Removing documentation build folder
echo.
echo Removing old build folders
echo --------------------------
rmdir /s /q .\docs\html 2> nul
echo ^> Done :)

:: Going back to the original directory
popd

:: Letting the user check the logs
echo.
pause
