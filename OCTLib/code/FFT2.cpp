/*******************************************************************************
*  $Id: FFT2.cpp 2 2010-01-05 03:34:41Z rosmir $
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
// need for FFT analysis
#include "./fftw3.h"

// for DLL export
extern "C" {
DllExport I8 OL_fft2(U32, U32, I8, I8,  DBL *, DBL *, DBL *, DBL *, DBL *);
}

/* FFT2 main function
  PURPOSE:
    calculate FFT (using fftw_plan_many_r2r() function call from FFTW library)
    for RAW B-scan without data pre-processing [1]
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    hann_flag - flag for Hanning window [2]
    dB_flag - flag for scale: linear or dB (20log())
    in - pointer to buffer with RAW B-scan before FFT (size: X * Y)
  
  OUTPUTS:
    intensity - pointer to buffer contained intensities, structural B-scan
    (size: (X / 2) * Y)
    phase - pointer to buffer contained phases, phase B-scan (size: (X / 2) * Y)
    Re - pointer to buffer contained real part of FFT (size: (X / 2) * Y)
    Im - pointer to buffer contained imaginary part of FFT (size: (X / 2) * Y)
  
  REMARKS:
    this function is experimental to test the FFTW way of multi-threading for
    FFT. The testing should be performed on computer with single dual-core
    processor.
  
  REFERENCES:
    [1] http://www.fftw.org/fftw3_doc/Advanced-Real_002dto_002dreal-Transforms.html
    [2] http://en.wikipedia.org/wiki/Hann_function 
*/
I8 OL_fft2(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, DBL *in, DBL *intensity,
           DBL *phase, DBL *Re, DBL *Im) {
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * X));
  DBL *tmp_fft_out = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * X * Y));
  I32 n = X;
  fftwf_r2r_kind fftkind = FFTW_R2HC;
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_many_r2r(1, &n, Y, tmp_fft_out, NULL, 1, X,
                                       tmp_fft_out, NULL, 1, X, &fftkind,
                                       FFTW_ESTIMATE);
  U32 width = static_cast<U32>(X/2);
  I32 j;
  // prepare Hanning window
  for (U32 i = 0; i < X; i++) {
    if (hann_flag)
      hann_win[i] = 0.5 * (1 - cos(kTwoPi * i / X));
    else
      hann_win[i] = 1.0;
  }
  // apply hanning window or just make data cast
  for (U32 i = 0; i < Y; i++)
    transform(in + i * X, in + (i + 1) * X, hann_win, tmp_fft_out + i * X,
              multiplies<DBL>());
  // perform multithreaded FFT using FFTW3 library
  fftw_init_threads();
  fftw_plan_with_nthreads(2);
  fftw_execute(fft_p);
  // parallel run by A-lines
  #pragma omp parallel for default(shared) private(j)
  for (j = 0; j < static_cast<I32>(Y); j++) {
    I32 _pos = j * X;
    I32 pos = j * width;
    // ZERO components
    if (dB_flag)
      intensity[pos] = 20 * log10(abs(tmp_fft_out[_pos]));
    else
      intensity[pos] = tmp_fft_out[_pos];
    Re[pos] = tmp_fft_out[_pos];
    phase[pos] = Im[pos] = 0.0;
    // construct intensity and phase information, Re and Im parts
    for (U32 pos1 = 1, pos2 = X - 1; pos1 < width; pos1++, pos2--) {
      // intensity
      if (dB_flag)
        intensity[pos + pos1] = 20 * log10(sqrt(tmp_fft_out[pos1 + _pos] * \
                                tmp_fft_out[pos1 + _pos] + \
                                tmp_fft_out[pos2 + _pos] * \
                                tmp_fft_out[pos2 + _pos]));
      else
        intensity[pos + pos1] = sqrt(tmp_fft_out[pos1 + _pos] * \
                                tmp_fft_out[pos1 + _pos] + \
                                tmp_fft_out[pos2 + _pos] * \
                                tmp_fft_out[pos2 + _pos]);
      // phase
      phase[pos + pos1] = atan2(tmp_fft_out[pos2 + _pos],
                                tmp_fft_out[pos1 + _pos]);
      // Re part
      Re[pos + pos1] = tmp_fft_out[pos1 + _pos];
      // Im part
      Im[pos + pos1] = tmp_fft_out[pos2 + _pos];
    }
  }  // end of parallel code
  fftw_destroy_plan(fft_p);
  fftw_free(hann_win);
  fftw_free(tmp_fft_out);
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
