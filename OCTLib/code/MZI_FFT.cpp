/*******************************************************************************
*  $Id: MZI_FFT.cpp 18 2010-01-11 05:26:47Z rosmir $
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
DllExport I8 OL_mzi_fft_i16(U32, U32, U32, I8, I8,  U32 *, I16 *, DBL *, DBL *,
                            DBL *, DBL *);
DllExport I8 OL_mzi_fft_u16(U32, U32, U32, I8, I8,  U32 *, U16 *, DBL *, DBL *,
                            DBL *, DBL *);
DllExport I8 OL_mzi_fft_i32(U32, U32, U32, I8, I8,  U32 *, I32 *, DBL *, DBL *,
                            DBL *, DBL *);
DllExport I8 OL_mzi_fft_u32(U32, U32, U32, I8, I8,  U32 *, U32 *, DBL *, DBL *,
                            DBL *, DBL *);
DllExport I8 OL_mzi_fft_sgl(U32, U32, U32, I8, I8,  U32 *, SGL *, DBL *, DBL *,
                            DBL *, DBL *);
DllExport I8 OL_mzi_fft_dbl(U32, U32, U32, I8, I8,  U32 *, DBL *, DBL *, DBL *,
                            DBL *, DBL *);
}

/* MZI + FFT main function
  PURPOSE:
    calculate FFT (using fftw_plan_r2r_1d() function call from FFTW library) for
    RAW B-scan pre-processed using k-clock or k-space clock approach [1][2]. The
    MZI indexes 1D array is used to pick up the sample points from each A-line
    for passing through FFT, all other points are ignored. All selected points
    are considered to be linear and equispaced in k-space. Ignored points are
    not interpolated to keep fast processing. Initially the MZI indexes 1D array
    should be generated using a Mach-Zehnder interferometer (MZI) with both
    output ports recorded in dual balanced detection mode.
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    mzi_length - number of MZI indexes
    hann_flag - flag for Hanning window [3]
    dB_flag - flag for scale: linear or dB (20log())
    mzi_indexes - MZI indexes
    in - pointer to buffer with RAW B-scan before FFT (size: X * Y)
  
  OUTPUTS:
    intensity - pointer to buffer contained intensities, structural B-scan
    (size: (mzi_length / 2) * Y)
    phase - pointer to buffer contained phases, phase B-scan
    (size: (mzi_length / 2) * Y)
    Re - pointer to buffer contained real part of FFT
    (size: (mzi_length / 2) * Y)
    Im - pointer to buffer contained imaginary part of FFT
    (size: (mzi_length / 2) * Y)
  
  REMARKS:
    note that mzi_length should be less X more than three times to keep
    resolution of obtained OCT B-scans reasonable. Thus, if you want to use the
    whole length of each A-line consider the lin_interpl_FFT.cpp, and
    spline_FFT.cpp files.
    note that in case of hardware k-clock, or k-space clock (k-trigger) the A/Q
    board should pick up samples already linear and equispaced in k-space. In
    this case use FFT.cpp file.
  
  REFERENCES:
    [1] http://www.fftw.org/fftw3_doc/Real_002dto_002dReal-Transforms.html
    [2] R. Huber, M. Wojtkowski, J.G. Fujimoto, J. Y. Jiang, and A. E. Cable,
    "Three-dimensional and C-mode OCT imaging with a compact, frequency swept
    laser source at 1300 nm", Opt. Express 13, 10523 (2005). You can obtain it
    from https://www.thorlabs.com/OCT/files/Optics_Express_Fujimoto_2005.pdf
    [3] http://en.wikipedia.org/wiki/Hann_function
*/
template <typename T1>
I8 mzi_fft(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
           U32 *mzi_indexes, T1 *in, DBL *intensity, DBL *phase, DBL *Re,
           DBL *Im) {
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * mzi_length));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(mzi_length, Re, Im, FFTW_R2HC,
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
    Re[pos] = tmp_fft_out[0];
    phase[pos] = Im[pos] = 0.0;
    // construct intensity and phase information, Re and Im parts
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
      // Re part
      Re[pos + pos1] = tmp_fft_out[pos1];
      // Im part
      Im[pos + pos1] = tmp_fft_out[pos2];
    }
    fftw_free(tmp_fft_in);
    fftw_free(tmp_fft_out);
  }  // end of parallel code
  fftw_destroy_plan(fft_p);
  fftw_free(hann_win);
  return EXIT_SUCCESS;
}

/************OL_mzi_fft************/
// MZI + FFT for I16
I8 OL_mzi_fft_i16(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, I16 *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

// MZI + FFT for U16
I8 OL_mzi_fft_u16(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, U16 *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

// MZI + FFT for I32
I8 OL_mzi_fft_i32(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, I32 *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

// MZI + FFT for U32
I8 OL_mzi_fft_u32(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, U32 *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

// MZI + FFT for SGL
I8 OL_mzi_fft_sgl(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, SGL *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

// MZI + FFT for DBL
I8 OL_mzi_fft_dbl(U32 X, U32 Y, U32 mzi_length, I8 hann_flag, I8 dB_flag,
                  U32 *mzi_indexes, DBL *in, DBL *intensity, DBL *phase,
                  DBL *Re, DBL *Im) {
  return mzi_fft(X, Y, mzi_length, hann_flag, dB_flag, mzi_indexes, in,
                 intensity, phase, Re, Im);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
