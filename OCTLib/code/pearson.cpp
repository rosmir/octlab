/*******************************************************************************
*  $Id: pearson.cpp 59 2010-02-15 03:49:14Z rosmir $
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
DllExport I8 OL_pearson_map(U32, U32, U32, U32, DBL *, DBL *, DBL *);
}

/* pearson_map main function
  PURPOSE:
    calculate Pearson product-moment correlation coefficient for spatially
    sliding 2D window within B-scan [1].
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    x_d - cell height (Fortran-style), defines width of 2D sliding window
    (C-style)
    y_d - cell width (Fortran-style), defines height of 2D sliding window
    (C-style)
    in1 - pointer to first buffer with B-scan after FFT (size: X * Y)
    in2 - pointer to second buffer with another B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: (X - x_d) * (Y - y_d))
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Pearson_product-moment_correlation_coefficient
*/
I8 OL_pearson_map(U32 X, U32 Y, U32 x_d, U32 y_d, DBL *in1, DBL *in2,
                  DBL *out) {
  U32 size = x_d * y_d;
  I32 x, y, d = X - x_d;
  // simple checks
  if (size < 2) return EXIT_FAILURE;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < static_cast<I32>(Y - y_d); y++) {  // vertical
    for (x = 0; x < d; x++) {  // horizontal
      DBL sum_x = 0.0, sum_y = 0.0, sumxy = 0.0, sumx2 = 0.0, sumy2 = 0.0;
      // loop for pearson
      for (U32 i = x; i < x_d + x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
            sum_x = sum_x + in1[pos];
            sum_y = sum_y + in2[pos];
            sumxy = sumxy + in1[pos] * in2[pos];
            sumx2 = sumx2 + in1[pos] * in1[pos];
            sumy2 = sumy2 + in2[pos] * in2[pos];
        }
      }
      // fill out
      out[y * d + x] = (size * sumxy - sum_x * sum_y) / \
                       (sqrt((size * sumx2 - sum_x * sum_x) * \
                       (size * sumy2 - sum_y * sum_y)));
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
