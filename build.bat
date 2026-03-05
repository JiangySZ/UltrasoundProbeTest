@echo off
set QTDIR=C:\Qt\Qt5.9.1\5.9.1\msvc2017_64

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cd /d G:\AI_WORk\Sys_Prb_Test

"%QTDIR%\bin\qmake.exe" UltrasoundProbeTest.pro -spec win32-msvc CONFIG+=debug

nmake -f Makefile.Debug

echo.
echo Build completed!
echo Setting Qt PATH and running...
set PATH=%QTDIR%\bin;%PATH%

debug\UltrasoundProbeTest.exe
