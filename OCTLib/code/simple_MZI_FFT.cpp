/*******************************************************************************
*  $Id: simple_MZI_FFT.cpp 25 2010-01-19 05:47:46Z rosmir $
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

/* simple MZI + FFT main function
  PURPOSE:
    calculate simple FFT (using fftw_plan_r2r_1d() function call from FFTW
    library) for RAW B-scan pre-processed using k-clock or k-space clock
    approach. Read description for MZI_FFT.cpp file for more details.
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    mzi_length - number of MZI indexes
    hann_flag - flag for Hanning window
    dB_flag - flag for scale: linear or dB (20log())
    mzi_indexes - MZI indexes
    in - pointer to buffer with RAW B-scan before FFT (size: X * Y)
  
  OUTPUTS:
    intensity - pointer to buffer contained intensities, structural B-scan
    (size: (mzi_length / 2) * Y)
    phase - pointer to buffer contained phases, phase B-scan
    (size: (mzi_length / 2) * Y)
  
    REMARKS:
    note that this function does not return Im and Re parts after FFT. Use
    MZI_FFT.cpp file to obtain them.
*/
extern "C" {
DllExport I8 OL_simple_mzi_fft_i16(U32, U32, U32, I8, I8,  U32 *, I16 *, DBL *,
                                   DBL *);
DllExport I8 OL_simple_mzi_fft_u16(U32, U32, U32, I8, I8,  U32 *, U16 *, DBL *,
                                   DBL *);
DllExport I8 OL_simple_mzi_fft_i32(U32, U32, U32, I8, I8,  U32 *, I32 *, DBL *,
                                   DBL *);
DllExport I8 OL_simple_mzi_fft_u32(U32, U32, U32, I8, I8,  U32 *, U32 *, DBL *,
                                   DBL *);
DllExport I8 OL_simple_mzi_fft_sgl(U32, U32, U32, I8, I8,  U32 *, SGL *, DBL *,
                                   DBL *);
DllExport I8 OL_simple_mzi_fft_dbl(U32, U32, U32, I8, I8,  U32 *, DBL *, DBL *,
                                   DBL *);
}

// simple MZI + FFT main function
template <typename T1>
I8 simple_mzi_fft(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, T1 *in, DBL *intensity, DBL *phase) {
  // simple checks
  if (mzi_length < 2) return EXIT_FAILURE;
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * mzi_length));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(mzi_length, intensity, phase, FFTW_R2HC,
                                     FFTW_ESTIMATE);
  U32 width = static_cast<U32>(mzi_length/2);
  I32 j;
  // prepare Hanning window
  for (U32 i = 0; i < mzi_length; i++) {
    if (hann_flag)
      hann_win[i] = 0.5 * (1 - cos(kTwoPi * i / mzi_length));
    else
      hann_win[i] = 1.0;
  }
  // parallel run by A-lines
  #pragma omp parallel for default(shared) private(j)
  for (j = 0; j < static_cast<I32>(Y); j++) {
    DBL *tmp_fft_in = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * mzi_length));
    DBL *tmp_fft_out =static_cast<DBL *>(fftw_malloc(sizeof(DBL) * mzi_length));
    I32 pos = j * width;
    // MZI filter: pick up RAW A-line values for corresponding MZI indexes
    for (U32 i = 0; i < mzi_length; i++)
      tmp_fft_in[i] = in[j * X + mzi_indexes[i]];
    // apply hanning window or just make data cast
    transform(tmp_fft_in, tmp_fft_in + mzi_length, hann_win, tmp_fft_in,
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
    for (U32 pos1 = 1, pos2 = mzi_length - 1; pos1 < width; pos1++, pos2--) {
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

/************OL_simple_mzi_fft************/
// simpe MZI + FFT for I16
I8 OL_simple_mzi_fft_i16(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, I16 *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

// simple MZI + FFT for U16
I8 OL_simple_mzi_fft_u16(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, U16 *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

// simple MZI + FFT for I32
I8 OL_simple_mzi_fft_i32(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, I32 *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

// simple MZI + FFT for U32
I8 OL_simple_mzi_fft_u32(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, U32 *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

// simple MZI + FFT for SGL
I8 OL_simple_mzi_fft_sgl(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, SGL *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

// simple MZI + FFT for DBL
I8 OL_simple_mzi_fft_dbl(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                         U32 *mzi_indexes, DBL *in, DBL *intensity,
                         DBL *phase) {
  return simple_mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                        intensity, phase);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
