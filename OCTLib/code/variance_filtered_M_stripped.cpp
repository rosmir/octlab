/*******************************************************************************
*  $Id: variance_filtered_M_stripped.cpp 59 2010-02-15 03:49:14Z rosmir $
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
DllExport I8 OL_variance_map_fl_M(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *);
}

/* variance_map with filtering for M-stripped data main function
  PURPOSE:
    calculate speckle variance for B-scan stripped by M-mode strips, then filter
    obtained variance values based on intensity information. If intensity is out
    of defined range the variance value is zero. Read description for
    variance.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    stripsize - width of M-mode strips within B-scan
    offset - start position of first M-mode strip within B-scan
    min - minimum value for intensity range
    max - maximum value for intensity range
    in - pointer to buffer with B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: ((Y - offset) / stripsize) * X)
*/
I8 OL_variance_map_fl_M(U32 X, U32 Y, U32 stripsize, U32 offset, DBL min,
                        DBL max, DBL *in, DBL *out) {
  // simple checks
  if (stripsize < 2) return EXIT_FAILURE;
  I32 d = (Y - offset) / stripsize;
  if (d < 2) return EXIT_FAILURE;
  DBL _max = max * stripsize, _min = min * stripsize;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < d; y++) {  // vertical
    for (x = 0; x < static_cast<I32>(X); x++) {  // horizontal
      DBL sum = 0.0, sum2 = 0.0;
      // loop for mean
      for (U32 j = 0, pos = (y * stripsize + offset) * X + x; j < stripsize;
           j++, pos = pos + X) {
        // sum
        sum = sum + in[pos];
        // sum^2
        sum2 = sum2 + in[pos] * in[pos];
      }
      // fill out
      if ((sum > _max) || (sum < _min))
        out[y * X + x] = 0.0;
      else
        out[y * X + x] = (sum2 - sum * sum / stripsize) / (stripsize - 1);
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
