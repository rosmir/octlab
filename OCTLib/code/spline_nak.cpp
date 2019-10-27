/*******************************************************************************
*  $Id: spline_nak.cpp 3 2010-01-06 03:32:00Z rosmir $
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
// header for spline interpolation
#include "./interp.h"

// for DLL export
extern "C" {
DllExport I8 OL_spline_nak(U32, U32, DBL *, DBL *, DBL *, DBL *);
}

/* spline_nak interpolation main function
  PURPOSE:
    convert 1D data row from one space to another using 'not-a-knot' spline
    interpolation (see interp.cpp file for more details).
  
  INPUTS:
    n - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    x - pointer to initial space (SIZE: n)
    XX - pointer to final space (SIZE: n)
    in - pointer to buffer with RAW B-scan before spline interpolation
    (size: n * Y)
  
  OUTPUTS:
    out - pointer to buffer with converted RAW B-scan after spline interpolation
    (size: n * Y)
  
  REMARKS:
    this function is experimental to test the spline interpolation. This
    function is the part of spline_FFT.cpp file.
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Spline_interpolation#Cubic_spline_interpolation
*/
I8 OL_spline_nak(U32 n, U32 Y, DBL *x, DBL *XX, DBL *in, DBL *out) {
  I32 i;
  #pragma omp parallel for default(shared) private(i)
  for (i = 0; i < static_cast<I32>(Y); i++) {
    DBL *b = new DBL[n];
    DBL *c = new DBL[n];
    DBL *d = new DBL[n];
    cubic_nak(n, x, in + n * i, b, c, d);
    for (U32 j = 0; j < n; j++)
      out[n * i + j] = spline_eval(n, x, in + n * i, b, c, d, XX[j]);
    delete [] b;
    delete [] c;
    delete [] d;
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
