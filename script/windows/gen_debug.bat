@echo off
chcp 65001 >nul


set GENERATOR="Visual Studio 16 2019"
set ARCH=x64
set BUILD_TYPE=Debug

cd ../../

cmake -G %GENERATOR% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%   -DCMAKE_PREFIX_PATH="C:/Qt/6.10.0/msvc2022_64" -B build


pause