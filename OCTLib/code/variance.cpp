/*******************************************************************************
*  $Id: variance.cpp 59 2010-02-15 03:49:14Z rosmir $
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
DllExport I8 OL_variance_map(U32, U32, U32, U32, DBL *, DBL *);
}

/* OL_variance_map main function
  PURPOSE:
    calculate speckle variance for spatially sliding 2D window within B-scan.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    x_d - cell height (Fortran-style), defines width of 2D sliding window
    (C-style)
    y_d - cell width (Fortran-style), defines height of 2D sliding window
    (C-style)
    in - pointer to buffer with B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: (X - x_d) * (Y - y_d))
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Variance
    [2] http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
    [3] http://en.wikipedia.org/wiki/Bessel's_correction
*/
I8 OL_variance_map(U32 X, U32 Y, U32 x_d, U32 y_d, DBL *in, DBL *out) {
  U32 size = x_d * y_d;
  I32 x, y, d = X - x_d;
  // simple checks
  if (size < 2) return EXIT_FAILURE;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < static_cast<I32>(Y - y_d); y++) {  // vertical
    for (x = 0; x < d; x++) {  // horizontal
      DBL sum = 0.0, sum2 = 0.0;
      // loop for mean
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // sum
          sum = sum + in[pos];
          // sum^2
          sum2 = sum2 + in[pos] * in[pos];
        }
      }
      // fill out
      out[y * d + x] = (sum2 - sum * sum / size) / (size - 1);
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
