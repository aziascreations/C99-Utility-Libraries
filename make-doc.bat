@echo off

:: Going into the script's directory
pushd %~dp0

:: ...
cd docs

:: Making the documentation
rmdir html /s /q
doxygen

:: Copying files shared between the repo and doc's readme.
:: The have different paths and this was the easiest way to go about it.
mkdir "html/docs"
mkdir "html/docs/images"
mkdir "html/examples"
xcopy "images" "html/docs/images" /E /H
xcopy "../examples" "html/examples" /E /H

:: ??? - WTF was this supposed to accomplish ?
::copy "..\make-doc.bat" "html\make-doc.bat"

:: Going back to the original directory
popd
