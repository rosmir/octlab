/*******************************************************************************
*  $Id: contrast_filtered_M_stripped.cpp 63 2010-02-17 03:29:22Z rosmir $
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
DllExport I8 OL_contrast_map_fl_M(U32, U32, U32, U32, DBL, DBL, DBL *, DBL *);
}

/* contrast_map with filtering for M-stripped data main function
  PURPOSE:
    calculate speckle contrast for B-scan stripped by M-mode strips, then filter
    obtained contrast values based on intensity information. If intensity is out
    of defined range the contrast values is zero. Read description for
    contrast.cpp file for more details.
  
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
I8 OL_contrast_map_fl_M(U32 X, U32 Y, U32 stripsize, U32 offset, DBL min,
                        DBL max, DBL *in, DBL *out) {
  // simple checks
  if (stripsize < 2) return EXIT_FAILURE;
  I32 d = (Y - offset) / stripsize;
  if (d < 2) return EXIT_FAILURE;
  I32 x, y;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < d; y++) {  // vertical
    for (x = 0; x < static_cast<I32>(X); x++) {  // horizontal
      DBL mean = 0.0;
      // loop for mean
      for (U32 j = 0, pos = (y * stripsize + offset) * X + x; j < stripsize;
           j++, pos = pos + X) {
        // sum
        mean = mean + in[pos];
      }
      mean = mean / stripsize;
      // fill out
      if ((mean > max) || (mean < min)) {
        out[y * X + x] = 0.0;
      } else {
        DBL  tmp = 0.0;
        // loop for contrast
        for (U32 j = 0, pos = (y * stripsize + offset) * X + x; j < stripsize;
          j++, pos = pos + X) {
          // sum^2
          tmp = tmp + (in[pos] - mean) * (in[pos] - mean);
        }
        out[y * X + x] = sqrt(tmp / (stripsize - 1)) / mean;
      }
    }
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
