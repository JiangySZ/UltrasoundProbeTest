@echo off
set QMAKESPEC=win32-msvc
set QTDIR=C:\Qt\Qt5.9.1\5.9.1\msvc2017_64

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cd /d G:\AI_WORk\Sys_Prb_Test

"%QTDIR%\bin\qmake.exe" UltrasoundProbeTest.pro -spec %QMAKESPEC% CONFIG+=debug

nmake -f Makefile.Debug
