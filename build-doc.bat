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
mkdir "html/extra"
xcopy "images" "html/docs/images" /E /H
xcopy "../examples" "html/examples" /E /H
xcopy "../extra" "html/extra" /E /H

:: xcopy is refusing to copy single files, it either does fuck all or whines about cyclic copies.
:: I'll use a simpler method that WORKS WHEN ASKED TO DO ITS ONLY JOB, unlike xcopy which just whines in the terminal !
type ..\LICENSE-CC0 > "html\LICENSE-CC0"
type ..\LICENSE-MIT > "html\LICENSE-MIT"

:: Going back to the original directory
popd
