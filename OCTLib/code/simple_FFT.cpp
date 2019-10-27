/*******************************************************************************
*  $Id: simple_FFT.cpp 19 2010-01-11 18:52:37Z rosmir $
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
DllExport I8 OL_simple_fft_i16(U32, U32, I8, I8,  I16 *, DBL *, DBL *);
DllExport I8 OL_simple_fft_u16(U32, U32, I8, I8,  U16 *, DBL *, DBL *);
DllExport I8 OL_simple_fft_i32(U32, U32, I8, I8,  I32 *, DBL *, DBL *);
DllExport I8 OL_simple_fft_u32(U32, U32, I8, I8,  U32 *, DBL *, DBL *);
DllExport I8 OL_simple_fft_sgl(U32, U32, I8, I8,  SGL *, DBL *, DBL *);
DllExport I8 OL_simple_fft_dbl(U32, U32, I8, I8,  DBL *, DBL *, DBL *);
}

/* simple FFT main function
  PURPOSE:
    calculate simple FFT (using fftw_plan_r2r_1d() function call from FFTW
    library) for RAW B-scan without data pre-processing [1]
  
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
  
  REMARKS:
    note that this function does not return Im and Re parts after FFT. Use
    FFT.cpp file to obtain them.
  
  REFERENCES:
    [1] http://www.fftw.org/fftw3_doc/Real_002dto_002dReal-Transforms.html
    [2] http://en.wikipedia.org/wiki/Hann_function 
*/
template <typename T1>
I8 simple_fft(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, T1 *in, DBL *intensity,
              DBL *phase) {
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * X));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(X, intensity, phase, FFTW_R2HC,
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
  // parallel run by A-lines
  #pragma omp parallel for default(shared) private(j)
  for (j = 0; j < static_cast<I32>(Y); j++) {
    DBL *tmp_fft_in = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * X));
    DBL *tmp_fft_out = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * X));
    I32 pos = j * width;
    // apply hanning window or just make data cast
    transform(in + j * X, in + (j + 1) * X, hann_win, tmp_fft_in,
              multiplies<DBL>());
    // perform FFT using FFTW3 library
    fftw_execute_r2r(fft_p, tmp_fft_in, tmp_fft_out);
    // ZERO components
    if (dB_flag)
      intensity[pos] = 20 * log10(abs(tmp_fft_out[0]));
    else
      intensity[pos] = tmp_fft_out[0];
    phase[pos] = 0.0;
    // construct intensity and phase information
    for (U32 pos1 = 1, pos2 = X - 1; pos1 < width; pos1++, pos2--) {
      // intensity
      if (dB_flag)
        intensity[pos + pos1] = 20 * log10(sqrt(tmp_fft_out[pos1] * \
                                tmp_fft_out[pos1] + tmp_fft_out[pos2] * \
                                tmp_fft_out[pos2]));
      else
        intensity[pos + pos1] = sqrt(tmp_fft_out[pos1] * tmp_fft_out[pos1] + \
                                tmp_fft_out[pos2] * tmp_fft_out[pos2]);
      // phase
      phase[pos + pos1] = atan2(tmp_fft_out[pos2], tmp_fft_out[pos1]);
    }
    fftw_free(tmp_fft_in);
    fftw_free(tmp_fft_out);
  }  // end of parallel code
  fftw_destroy_plan(fft_p);
  fftw_free(hann_win);
  return EXIT_SUCCESS;
}

/************OL_simple_fft************/
// simple FFT for I16
I8 OL_simple_fft_i16(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, I16 *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

// simple FFT for U16
I8 OL_simple_fft_u16(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, U16 *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

// simple FFT for I32
I8 OL_simple_fft_i32(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, I32 *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

// simple FFT for U32
I8 OL_simple_fft_u32(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, U32 *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

// simple FFT for SGL
I8 OL_simple_fft_sgl(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, SGL *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

// simple FFT for DBL
I8 OL_simple_fft_dbl(U32 X, U32 Y, I8 hann_flag, I8 dB_flag, DBL *in,
                     DBL *intensity, DBL *phase) {
  return simple_fft(X, Y, hann_flag, dB_flag, in, intensity, phase);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
