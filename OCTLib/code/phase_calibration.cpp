/*******************************************************************************
*  $Id: phase_calibration.cpp 25 2010-01-19 05:47:46Z rosmir $
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
DllExport I8 OL_phase_calibration(U32, U32, U32, DBL *, DBL *);
}

/* phase calibration main function
  PURPOSE:
    calculate corrected phase based on phase information from calibration mirror
    [1].
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    level - the depth position of calibration mirror reflector
    ref - pointer to buffer with phase B-scan after FFT from calibration mirror
    (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with phase B-scan after FFT from sample
    (size: X * Y)
  
  REMARKS:
    note that for all depth indexes below level the phase correction is taken
    without calibration coefficient.
  
  REFERENCES:
    [1] B. J. Vakoc, S. H. Yun, J. F. de Boer, G. J. Tearney, and B. E. Bouma,
    "Phase-resolved optical frequency domain imaging", Opt. Express 13,
    5483-5493 (2005)
*/
I8 OL_phase_calibration(U32 X, U32 Y, U32 level, DBL *ref, DBL *ptr) {
  I32 i, j;
  // simple checks
  if (level < 1) return EXIT_FAILURE;
  #pragma omp parallel for default(shared) private(i, j)
  for (i = 0; i < static_cast<I32>(Y); i++)
    for (j =  0; j < static_cast<I32>(X); j++)
      if (j < static_cast<I32>(level))
        ptr[i * X + j] = ptr[i * X + j] - ref[i] * j / level;
      else
        ptr[i * X + j] = ptr[i * X + j] - ref[i];
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
