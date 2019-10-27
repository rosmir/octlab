/*******************************************************************************
*  $Id: simple_threshold.cpp 4 2010-01-06 05:06:20Z rosmir $
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

// for DLL export
extern "C" {
DllExport I8 OL_simple_threshold(U32, DBL, DBL, DBL *);
}

/* simple threshold main function
  PURPOSE:
    make data filtering. Value is kept if it is inside defined range
    (min...max), otherwise all values above max value are changed to max value,
    and all values below min value are changed to min value.
  
  INPUTS:
    SIZE - number of elements in buffer (B-scan)
    min - minimal value to check and to assigned
    max - maximum value to check and to assigned
  
  OUTPUTS:
    out - pointer to buffer with filtered B-scan after FFT (size: SIZE)
  
  REMARKS:
    note this function is useful to filter structural, intensity OCT B-scans.
*/
I8 OL_simple_threshold(U32 SIZE, DBL min, DBL max, DBL *ptr) {
  I32 i;
  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>(SIZE); i++) {
    if (ptr[i] > max)
      ptr[i] = max;
    else if (ptr[i] < min)
      ptr[i] = min;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
