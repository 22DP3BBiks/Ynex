@echo off
set "comLoc=cmake-build-debug"
set "testFolder=example"
if not exist "%cd%/%comLoc%/Ynex.exe" (
    echo "Could not find exe!"
    start /wait /b cmd /c "%ProgramFiles%/JetBrains/CLion 2022.2.3/bin/cmake/win/bin/cmake.exe" --build %USERPROFILE%\CLionProjects\Ynex/%comLoc% --target Ynex -- -j 3
    if %errorlevel% == 0 exit /b -1
)
for %%f in (%testFolder%/*.ynex) do (
    echo "Compiling %%~nf;"
    start /wait /b cmd /c "%cd%/%comLoc%/Ynex.exe" %cd%/%testFolder%/%%f %cd%/%testFolder%/%%~nf.cpp
    echo "%errorlevel%"
    if %errorlevel% NEQ 0 (echo "[31m[FAILED][0m") else (echo "[32m[SUCCESS][0m")
)
