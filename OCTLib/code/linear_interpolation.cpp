/*******************************************************************************
*  $Id: linear_interpolation.cpp 3 2010-01-06 03:32:00Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// standard headers
#include <algorithm>
#include <map>
// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport I8 OL_linear_interpl(U32, U32, DBL *, DBL *, DBL *);
}

/* linear interpolation main function
  PURPOSE:
    convert interferometric laser sweep (RAW A-line) from arbitrary wavelength
    space into linear wavenumber space (k-space) using linear interpolation [1].
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    start_wavelength - start of wavelength range for laser
    end_wavelength - end of wavelength range for laser
    in - pointer to buffer with RAW B-scan before linear interpolation
    (size: X * Y)
  
  OUTPUTS:
    in - pointer to buffer with converted RAW B-scan after linear interpolation
    (size: X * Y)
  
  REMARKS:
    this function is experimental to test the linear interpolation for
    arbitrary spectrum in wavelengths. This function is the part of
    lin_interpl_FFT.cpp file.
  
  REFERENCES:
    [1] http://en.wikipedia.org/wiki/Linear_interpolation
*/
I8 OL_linear_interpl(U32 X, U32 Y, DBL *spectrum, DBL *in, DBL *out) {
  I32 i, j;
  // initialize map
  map<DBL, I32> spectrum_map;
  I32 *li = new I32[X - 2];
  DBL *p = new DBL[X - 2];
  // load wavelength spectrum
  for (i = 0; i < static_cast<I32>(X); i++)
    spectrum_map.insert(DI_Pair(spectrum[i], i));
  DBL start_wavenumber = 1 / spectrum[0];
  // linear wavenumber step
  DBL wavenumber_step = (start_wavenumber - (1 / spectrum[X - 1])) / (X - 1);
  // coefficients and indexes for linear interpolation
  for (i = 1; i < static_cast<I32>(X - 1); i++) {
    // nonlinear wavelength corresponding to linear wavenumber
    DBL nl = 1 / (start_wavenumber - wavenumber_step * i);
    // close spectrum wavelength (its index) from left side
    li[i - 1] = find_index(&spectrum_map, nl);
    // the relative distance (in range 0...1) between linear and nonlinear
    // wavelengths calculated before
    p[i - 1] = (nl - spectrum[li[i - 1]]) / \
      (spectrum[li[i - 1] + 1] - spectrum[li[i - 1]]);
  }
  // parallel run by elements
  #pragma omp parallel for default(shared) private(i, j)
  for (i = 0; i < static_cast<I32>(Y); i++) {
    I32 pos = i * X;
    // keep first and last elements
    out[pos] = in[pos];
    out[pos + X - 1] = in[pos + X - 1];
    // linear interpolation
    // new value for calculated nonlinear wavelength but linear in wavenumber
    for (j = 0; j < static_cast<I32>(X - 2); j++)
      out[pos + j + 1] = (1 - p[j]) * in[pos + li[j]] + \
                         p[j] * in[pos + li[j] + 1];
  }  // end of parallel code
  delete [] li;
  delete [] p;
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
