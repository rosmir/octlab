/*******************************************************************************
*  $Id: Doppler_filtered_M_stripped.cpp 59 2010-02-15 03:49:14Z rosmir $
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
DllExport I8 OL_doppler_fltr_M(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *,
                               DBL *, DBL *);
}

/* Doppler OCT with filtering for M-stripped data main function
  PURPOSE:
    calculate Doppler frequency shifts using Kasai autocorrelation function
    for B-scan stripped by M-mode strips, then filter obtained phases based on
    intensity information. If intensity is out of defined range the phase is
    zero. Read description for Doppler.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    stripsize - width of M-mode strips within B-scan
    offset - start position of first M-mode strip within B-scan
    min - minimum value for intensity range
    max - maximum value for intensity range
    intensity - pointer to buffer with intensities, structure B-scan after FFT
    (size: X * Y)
    Re - pointer to buffer with real part of B-scan after FFT (size: X * Y)
    Im - pointer to buffer with imaginary part of B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: ((Y - offset) / stripsize) * X)
*/
I8 OL_doppler_fltr_M(U32 X, U32 Y, U32 stripsize, U32 offset, DBL min, DBL max,
                     DBL *intensity, DBL *Re, DBL *Im, DBL *out) {
  // simple checks
  if (stripsize < 2) return EXIT_FAILURE;
  I32 x, y, d = (Y - offset) / stripsize;
  if (d < 2) return EXIT_FAILURE;
  DBL _max = max * (stripsize - 1), _min = min * (stripsize - 1);
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < d; y++) {  // vertical
    for (x = 0; x < static_cast<I32>(X); x++) {  // horizontal
      DBL tmp_1 = 0.0, tmp_2 = 0.0, sum = 0.0;
      for (U32 j = 0, pos = (y * stripsize + offset) * X + x; j < stripsize - 1;
           j++, pos = pos + X) {
        // Q(m)I(m+1) - I(m)Q(m+1)
        tmp_1 = tmp_1 + Im[pos] * Re[pos + X] - Re[pos] * Im[pos + X];
        // Q(m)Q(m+1) + I(m)I(m+1)
        tmp_2 = tmp_2 + Im[pos] * Im[pos + X] + Re[pos] * Re[pos + X];
        // mean value
        sum = sum + intensity[pos];
      }
      // fill out
      if ((sum > _max) || (sum < _min))
        out[y * X + x] = 0.0;
      else
        out[y * X + x] = atan2(tmp_1, tmp_2);
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
