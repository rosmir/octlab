@echo off
:: $Id: make64icc.bat 71 2010-03-07 06:04:48Z rosmir $

set MYPROG=OCTLib_64
set EXCLUDE.1=lin_regr
set EXCLUDE.2=peak_width

@call "%ICPP_COMPILER11%\bin\iclvars.bat" intel64

echo.

@ for %%A in (*.cpp) do icl /O2 /Qipo /Qalias-args- /Qprec-div- /arch:SSE3 /QaxSSE4.2 /EHsc /fp:fast=2 /Fo"../bin/" /I"../include/" /D "WIN64" /D "NDEBUG" /c /W5 /Qdiag-disable:383,1418,1419 /nologo /MT /Qopenmp /Qopenmp-link:static %%A
@ for /f "usebackq delims==. tokens=1-3" %%i in (`set EXCLUDE`) do del "../bin/%%k.obj"
rc /i "../include/" /d "NDEBUG" /d "WIN64" /l 0x409 /fo"../bin/%MYPROG%.res" OCTLib.rc
xilink /DLL /NOASSEMBLY /LIBPATH:../lib libfftw3-3-x64.lib /OPT:REF /MACHINE:X64 /NOLOGO /OUT:../bin/%MYPROG%.dll ../bin/*.obj ../bin/%MYPROG%.res
del "../bin/*.obj" "../bin/%MYPROG%.exp" "../bin/%MYPROG%.res" "../bin/%MYPROG%.dll.manifest"

echo %MYPROG% is compiled
