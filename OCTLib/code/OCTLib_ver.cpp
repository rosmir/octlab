/*******************************************************************************
*  $Id: OCTLib_ver.cpp 78 2010-03-12 04:41:29Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// common header
#include "./OCTLib.h"
#include "./ver.h"

#ifdef __GNUC__
  #define sprintf_s snprintf
#endif

// for DLL export
extern "C" {
DllExport I8 OCTLibVer(char *str_name, char *str_ver);
}

// OCTLibVer main function
I8 OCTLibVer(char *str_name, char *str_ver) {
  sprintf_s(str_ver, sizeof(OCTLIB_VER_STRING), "%s", OCTLIB_VER_STRING);
  sprintf_s(str_name, sizeof(OCTLIB_DLL_STRING), "%s", OCTLIB_DLL_STRING);
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
