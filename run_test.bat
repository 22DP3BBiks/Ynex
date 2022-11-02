@echo off
set "comLoc=./cmake-build-debug"
set "testFolder=./example"
for %%f in (%testFolder%/*.ynex) do (
    echo Compiling %%~nf;
    start /wait /b cmd /c "%cd%/%comLoc%/Ynex.exe" %cd%/%testFolder%/%%f %cd%/%testFolder%/%%~nf.cpp
    echo %errorlevel%
    if %errorlevel% NEQ 0 (echo [31m[FAILED][0m) ELSE (echo [32m[SUCCESS][0m)
)
