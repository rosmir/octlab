//
// $Id: ver.h 71 2010-03-07 06:04:48Z rosmir $
// Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
// All rights reserved.
// web-site: www.OCTLab.org
//
// Use of this source code is governed by a Clear BSD-style license that can be
// found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
// in the COPYRIGHT.TXT file
//

#ifndef __VER_H__
#define __VER_H__

#define OCTLIB_VER  0,0,7,1
#define OCTLIB_VER_STRING "0.0.7.1\0"
#ifdef WIN32
  #define OCTLIB_DLL_STRING "OCTLib.dll"
#else
  #define OCTLIB_DLL_STRING "OCTLib_64.dll"
#endif

#endif
