/*******************************************************************************
*  $Id: simple_Doppler.cpp 18 2010-01-11 05:26:47Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// standard headers
#include <functional>
#include <algorithm>
// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport I8 OL_simple_doppler(U32, U32, DBL *);
}

/* simple Doppler OCT main function
  PURPOSE:
    calculate Doppler frequency shifts by subtracting successive phase OCT
    A-scans [1][2].
  
  INPUTS:
    X - number of elements in each row (A-scan size)
    Y - number of rows (# of A-scans)
  
  OUTPUTS:
    ptr - pointer to buffer with phases (with phase differences after function
    processing) (size: X * Y)
  
  REMARKS:
    note that last row will contain ZEROs
  
  REFERENCES:
    [1] Y. Zhao, Z. Chen, C. Saxer, S. Xiang, J.F. de Boer, and J.S. Nelson,
    "Phase-resolved optical coherence tomography and optical Doppler tomography
    for imaging blood flow in human skin with fast scanning speed and high
    velocity sensitivity", Opt. Lett. 25, 114-116 (2000). You can obtain it from
    http://web.mit.edu/~fgreen/OldFiles/MacData/afs.course/2/2.717/OldFiles/www/doppler_oct_nelson_00.pdf
    [2] B. White, M. Pierce, N. Nassif, B. Cense, B. Park, G. Tearney, B. Bouma,
    T. Chen, and J. de Boer, "In vivo dynamic human retinal blood flow imaging
    using ultra-high-speed spectral domain optical Doppler tomography", Opt.
    Express 11, 3490-3497 (2003).
*/
I8 OL_simple_doppler(U32 X, U32 Y, DBL *ptr) {
  transform(ptr, ptr + (Y - 1) * X, ptr + X, ptr, minus<DBL>());
  fill(ptr + (Y - 1) * X, ptr + Y * X, 0.0);
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
