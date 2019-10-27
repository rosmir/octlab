/*******************************************************************************
*  $Id: spline_FFT.cpp 25 2010-01-19 05:47:46Z rosmir $
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
// header for spline interpolation
#include "./interp.h"
// need for FFT analysis
#include "./fftw3.h"

// for DLL export
extern "C" {
DllExport I8 OL_spline_fft_u8(U32, U32, U32, U32, I8, I8, DBL *, U8 *, DBL *,
                              DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_i16(U32, U32, U32, U32, I8, I8, DBL *, I16 *, DBL *,
                               DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_u16(U32, U32, U32, U32, I8, I8, DBL *, U16 *, DBL *,
                               DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_i32(U32, U32, U32, U32, I8, I8, DBL *, I32 *, DBL *,
                               DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_u32(U32, U32, U32, U32, I8, I8, DBL *, U32 *, DBL *,
                               DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_sgl(U32, U32, U32, U32, I8, I8, DBL *, SGL *, DBL *,
                               DBL *, DBL *, DBL *);
DllExport I8 OL_spline_fft_dbl(U32, U32, U32, U32, I8, I8, DBL *, DBL *, DBL *,
                               DBL *, DBL *, DBL *);
}

/* spline interpolation + FFT main function
  PURPOSE:
    calculate FFT (using fftw_plan_r2r_1d() function call from FFTW library) for
    RAW B-scan pre-processed using known (actual) laser spectrum (wavelengths vs
    time/spatial indexes) [1]. This function converts each RAW OCT A-line into
    linear wavenumber space (k-space) using spline interpolation from nonlinear
    in wavenumber space defined by actual laser spectrum (wavelengths vs
    time/spatial indexes) [2]. Read description for lin_interpl_FFT.cpp file for
    more details.
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    start_index - first index for spectrum (left RAW A-line cut-off)
    end_index - last index for spectrum (right RAW A-line cut-off)
    hann_flag - flag for Hanning window [3]
    dB_flag - flag for scale: linear or dB (20log())
    spectrum - pointer to line with spectrum in wavelengths (nm)
    in - pointer to buffer with RAW B-scan before FFT (size: X * Y)
  
  OUTPUTS:
    intensity - pointer to buffer contained intensities, structural B-scan
    (size: ((end_index - start_index) / 2) * Y)
    phase - pointer to buffer contained phases, phase B-scan
    (size: ((end_index - start_index) / 2) * Y)
    Re - pointer to buffer contained real part of FFT
    (size: ((end_index - start_index) / 2) * Y)
    Im - pointer to buffer contained imaginary part of FFT
    (size: ((end_index - start_index) / 2) * Y)
  
  REMARKS:
    note that this function is significantly slower than function from
    lin_interpl_FFT.cpp file. Use this function only for post-processing
    analysis of obtained OCT data.
  
  REFERENCES:
    [1] http://www.fftw.org/fftw3_doc/Real_002dto_002dReal-Transforms.html
    [2] http://en.wikipedia.org/wiki/Spline_interpolation#Cubic_spline_interpolation
    [3] http://en.wikipedia.org/wiki/Hann_function
*/
template <typename T1>
I8 spline_fft(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
              I8 dB_flag, DBL *spectrum, T1 *in, DBL *intensity, DBL *phase,
              DBL *Re, DBL *Im) {
  U32 size = end_index - start_index;
  // simple checks
  if (size < 2) return EXIT_FAILURE;
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  DBL *XXX = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(size, Re, Im, FFTW_R2HC, FFTW_ESTIMATE);
  U32 width = static_cast<U32>(size/2);
  DBL start_wavenumber = 1 / spectrum[0];
  // linear wavenumber step
  DBL wavenumber_step = (start_wavenumber - (1 / spectrum[size - 1])) / \
                        (size - 1);
  I32 j;
  // prepare Hanning window and linear and non-linear wavelength vectors
  for (U32 i = 0; i < size; i++) {
    if (hann_flag)
      hann_win[i] = 0.5 * (1 - cos(kTwoPi * i / size));
    else
      hann_win[i] = 1.0;
    // non-linear in wavelength but linear in wavenumber
    XXX[i] = 1 /(start_wavenumber - wavenumber_step * i);
  }
  // parallel run by A-lines
  #pragma omp parallel for default(shared) private(j)
  for (j = 0; j < static_cast<I32>(Y); j++) {
    DBL *tmp_fft_in = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    DBL *tmp_fft_out = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    DBL *b = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    DBL *c = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    DBL *d = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
    U32 pos = j * width;
    // spline interpolation
    copy(in + j * X + start_index, in + j * X + end_index, tmp_fft_out);
    cubic_nak(size, spectrum, tmp_fft_out, b, c, d);
    // apply hanning window or just get values
    for (U32 i = 0; i < size; i++) tmp_fft_in[i] =
      hann_win[i] * spline_eval(size, spectrum, tmp_fft_out, b, c, d, XXX[i]);
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
    for (U32 pos1 = 1, pos2 = size - 1; pos1 < width; pos1++, pos2--) {
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
    fftw_free(b);
    fftw_free(c);
    fftw_free(d);
  }  // end of parallel code
  fftw_destroy_plan(fft_p);
  fftw_free(hann_win);
  fftw_free(XXX);
  return EXIT_SUCCESS;
}

/************OL_spline_fft************/
// Spline + FFT for U8
I8 OL_spline_fft_u8(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                    I8 dB_flag, DBL *spectrum, U8 *in, DBL *intensity,
                    DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for I16
I8 OL_spline_fft_i16(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, I16 *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for U16
I8 OL_spline_fft_u16(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, U16 *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for I32
I8 OL_spline_fft_i32(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, I32 *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for U32
I8 OL_spline_fft_u32(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, U32 *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for SGL
I8 OL_spline_fft_sgl(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, SGL *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

// Spline + FFT for DBL
I8 OL_spline_fft_dbl(U32 X, U32 Y, U32 start_index, U32 end_index, I8 hann_flag,
                     I8 dB_flag, DBL *spectrum, DBL *in, DBL *intensity,
                     DBL *phase, DBL *Re, DBL *Im) {
  return spline_fft(X, Y, start_index, end_index, hann_flag, dB_flag, spectrum,
                    in, intensity, phase, Re, Im);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
