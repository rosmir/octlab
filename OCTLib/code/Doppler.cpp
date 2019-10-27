/*******************************************************************************
*  $Id: Doppler.cpp 59 2010-02-15 03:49:14Z rosmir $
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
DllExport I8 OL_doppler(U32, U32, U32, U32, DBL *, DBL *, DBL *);
}

/* Doppler OCT main function
  PURPOSE:
    calculate Doppler frequency shifts using Kasai autocorrelation function [1]
    for spatially sliding 2D window within B-scan [2].
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
    x_d - cell height (Fortran-style), defines width of 2D sliding window
    (C-style)
    y_d - cell width (Fortran-style), defines height of 2D sliding window
    (C-style)
    Re - pointer to buffer with real part of B-scan after FFT (size: X * Y)
    Im - pointer to buffer with imaginary part of B-scan after FFT (size: X * Y)
  
  OUTPUTS:
    out - pointer to buffer with results (size: (X - x_d) * (Y - y_d))
  
  REMARKS:
    note that last row will contain ZEROs
  
  REFERENCES:
    [1] C. Kasai, K. Namekawa, A. Koyano, and R. Omoto, "Real-time
    two-dimensional blood flow imaging using an autocorrelation technique",
    IEEE Trans. Sonics. Ultrason. 32, 458-464 (1985). You can obtain it from
    http://server.elektro.dtu.dk/personal/jaj/31545/documents/kasai_et_al_1985.pdf
    [2] V.X.D. Yang and I.A. Vitkin, Principles of Doppler Optical Coherence
    Tomography, in Handbook of Optical Coherence Tomography in Cardiology,
    edited by Evelyn Regar, Ton van Leeuwen and Patrick Serruys (Taylor and
    Francis Medical, Oxford, UK: 2006), chapter 32. You can obtain it from
    http://www.uhnres.utoronto.ca/labs/biophotonics/staff_papers/vitkin/Doppler_OCT_book_chapter_2007.pdf
*/
I8 OL_doppler(U32 X, U32 Y, U32 x_d, U32 y_d, DBL *Re, DBL *Im, DBL *out) {
  I32 x, y, d = X - x_d;
  U32 shift = (Y - y_d - 1) * d;
  // parallel run by elements
  #pragma omp parallel for default(shared) private(x, y)
  for (y = 0; y < static_cast<I32>(Y - y_d - 1); y++) {  // vertical
    for (x = 0; x < d; x++) {  // horizontal
      DBL tmp_1 = 0.0, tmp_2 = 0.0;
      for (U32 i = x; i < x_d+ x; i++) {
        for (U32 j = 0, pos = y * X + i; j < y_d; j++, pos = pos + X) {
          // Q(m)I(m+1) - I(m)Q(m+1)
          tmp_1 = tmp_1 + Im[pos] * Re[pos + X] - Re[pos] * Im[pos + X];
          // Q(m)Q(m+1) + I(m)I(m+1)
          tmp_2 = tmp_2 + Im[pos] * Im[pos + X] + Re[pos] * Re[pos + X];
        }
      }
      // fill out
      out[y * d + x] = atan2(tmp_1, tmp_2);
    }
    // zero filling
    out[shift + x] = 0.0;
  }  // end of parallel code
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
