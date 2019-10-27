/*******************************************************************************
*  $Id: simple_threshold2.cpp 4 2010-01-06 05:06:20Z rosmir $
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
DllExport I8 OL_simple_threshold2(U32, DBL, DBL, DBL, DBL, DBL *, DBL *);
}

/* simple threshold #2 main function
  PURPOSE:
    make data filtering based on reference. Value from data array is kept if the
    corresponding value from reference array is inside its defined range
    (min...max), otherwise values from data are changed to new_max for all
    corresponding values from reference array that are above max value, and
    values from data are changed to new_min for all corresponding values from
    reference that are below min value.
  
  INPUTS:
    SIZE - number of elements in buffer (B-scan)
    min - minimal intensity value to check
    max - maximum intensity value to check
    new_min - minimal phase value to assigned
    new_max - maximum phase value to assigned
    ref - pointer to buffer with intensity B-scan after FFT (size: SIZE)
  
  OUTPUTS:
    out - pointer to buffer with filtered Doppler OCT or phase B-scan after FFT
    (size: SIZE)
  
  REMARKS:
    note this function is useful to filter Doppler OCT results or phase OCT
    B-scans based on information from structural, intensity OCT B-scans.
*/
I8 OL_simple_threshold2(U32 SIZE, DBL min, DBL max, DBL new_min, DBL new_max,
                        DBL *ref, DBL *ptr) {
  I32 i;
  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>(SIZE); i++) {
    if (ref[i] > max)
      ptr[i] = new_max;
    else if (ref[i] < min)
      ptr[i] = new_min;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
