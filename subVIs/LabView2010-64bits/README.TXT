ATTENTION:
Use of this source code is governed by a Clear BSD-style license that can be
found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or in
the COPYRIGHT.TXT file

To use this 64-bit edition sub-VIs:
1) first, copy 64-bit edition DLLs from
https://github.com/rosmir/octlab/blob/master/subVIs/dll64 into System32 folder
(C:\WINDOWS\System32);
2) second, use LabView 2009 or above 64-bit edition;
3) third, install "Microsoft Visual C++ 2008 SP1 Redistributable Package (x64)"
from Microsoft web-site if after running LabView asks for OpenMP DLL (you do not
need to install it in case of Windows 7 64-bit edition).

NOTE! This sub-VIs and DLLs are NOT for 32-bit editions of LabView and 32-bit
editions of Windows.

NOTE! You should use polymorphic sub-VIs in bundle with OCTLab.llb!