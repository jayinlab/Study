@echo off
set pwd=%~dp0

if exist cmake-build-msvc (
echo build directory "cmake-build-msvc" already exist
pause
) else (
mkdir cmake-build-msvc && ^
cd cmake-build-msvc && ^
cmake .. && ^
cd "%pwd%" && ^
mkdir .\cmake-build-msvc\Debug\
copy .\3rdparty\angle\bin\windows-x64\*.dll .\cmake-build-msvc\Debug\
pause
)
