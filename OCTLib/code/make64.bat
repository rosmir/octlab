@echo off
:: $Id: make64.bat 71 2010-03-07 06:04:48Z rosmir $

set MYPROG=OCTLib_64
set EXCLUDE.1=lin_regr
set EXCLUDE.2=peak_width

@call "%VS90COMNTOOLS%\..\..\VC\vcvarsall.bat" amd64

echo.

@ for %%A in (*.cpp) do cl /O2 /favor:INTEL64 /EHsc /GL /GS- /fp:fast /Fo"../bin/" /I"../include/" /D "WIN64" /D "NDEBUG" /c /W4 /nologo /MT /openmp %%A
@ for /f "usebackq delims==. tokens=1-3" %%i in (`set EXCLUDE`) do del "../bin/%%k.obj"
rc /i "../include/" /d "NDEBUG" /d "WIN64" /l 0x409 /fo"../bin/%MYPROG%.res" OCTLib.rc
link /DLL /NOASSEMBLY /LIBPATH:../lib libfftw3-3-x64.lib /OPT:REF /MACHINE:X64 /NOLOGO /LTCG /OUT:../bin/%MYPROG%.dll ../bin/*.obj ../bin/%MYPROG%.res
mt -nologo -manifest "../bin/%MYPROG%.dll.manifest" -outputresource:"../bin/%MYPROG%.dll";2
del "../bin/*.obj" "../bin/%MYPROG%.exp" "../bin/%MYPROG%.res" "../bin/%MYPROG%.dll.manifest"

echo %MYPROG% is compiled
