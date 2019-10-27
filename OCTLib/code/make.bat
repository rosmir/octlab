@echo off
:: $Id: make.bat 64 2010-02-19 06:11:33Z rosmir $

set MYPROG=OCTLib
set EXCLUDE.1=lin_regr
set EXCLUDE.2=peak_width

@call "%VS90COMNTOOLS%\vsvars32.bat"

echo.

@ for %%A in (*.cpp) do cl /O2 /EHsc /GL /GS- /Gd /arch:SSE2 /fp:fast /Fo"../bin/" /I"../include/" /D "WIN32" /D "NDEBUG" /c /W4 /nologo /MT /openmp %%A
@ for /f "usebackq delims==. tokens=1-3" %%i in (`set EXCLUDE`) do del "../bin/%%k.obj"
rc /i "../include/" /d "NDEBUG" /d "WIN32" /l 0x409 /fo"../bin/%MYPROG%.res" %MYPROG%.rc
link /DLL /NOASSEMBLY /LIBPATH:../lib libfftw3-3.lib /OPT:REF /MACHINE:X86 /NOLOGO /LTCG /OUT:../bin/%MYPROG%.dll ../bin/*.obj ../bin/%MYPROG%.res
mt -nologo -manifest "../bin/%MYPROG%.dll.manifest" -outputresource:"../bin/%MYPROG%.dll";2
del "../bin/*.obj" "../bin/%MYPROG%.exp" "../bin/%MYPROG%.res" "../bin/%MYPROG%.dll.manifest"

echo %MYPROG% is compiled
