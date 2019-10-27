/*******************************************************************************
*  $Id: simple_Doppler_filtered.cpp 18 2010-01-11 05:26:47Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// standart headers
#include <functional>
#include <algorithm>
// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport I8 OL_simple_doppl_fl(U32, U32, DBL, DBL, DBL *, DBL *);
}

/* simple Doppler OCT with filtering main function
  PURPOSE:
    calculate Doppler frequency shifts by subtracting successive phase OCT
    A-scans, then filter obtained phase differences based on intensity
    information. If intensity is out of defined range the phase difference is
    zero. Read description for simple_Doppler.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    min - minimum value for intensity range
    max - maximum value for intensity range
    ref - pointer to buffer with intensities, structure B-scan after FFT
    (size: X * Y)
  
  OUTPUTS:
    ptr - pointer to buffer with phases (with phase differences after function
    processing) (size: X * Y)
  
  REMARKS:
    note that last row will contain ZEROs
*/
I8 OL_simple_doppl_fl(U32 X, U32 Y, DBL min, DBL max, DBL *ref, DBL *ptr) {
  I32 i;

  transform(ptr, ptr + (Y - 1) * X, ptr + X, ptr, minus<DBL>());
  fill(ptr + (Y - 1) * X, ptr + Y * X, 0.0);

  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>((Y - 1) * X); i++) {
    if (ref[i] > max)
      ptr[i] = 0.0;
    else if (ref[i] < min)
      ptr[i] = 0.0;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
