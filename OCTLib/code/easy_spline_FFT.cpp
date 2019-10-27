/*******************************************************************************
*  $Id: easy_spline_FFT.cpp 3 2010-01-06 03:32:00Z rosmir $
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
DllExport I8 OL_easy_spline_fft(U32, U32, U32, U32, DBL, DBL, I8, I8, DBL *,
                                DBL *, DBL *, DBL *, DBL *);
}

/* easy spline interpolation + FFT main function
  PURPOSE:
    calculate FFT (using fftw_plan_r2r_1d() function call from FFTW library) for
    RAW B-scan [1] converted into linear wavenumber space (k-space) from linear
    wavelength space using spline interpolation [2].
    NOTE! For spectral domain optical coherence tomography (SD-OCT) the spectrum
    can be less RAW A-line, thus, define the range to select only spectrum part
    of each RAW A-line within start_index and end_index parameters.
  
  INPUTS:
    X - number of elements in each row (RAW A-line size)
    Y - number of rows (# of RAW A-lines)
    start_index - first index for spectrum (left RAW A-line cut-off)
    end_index - last index for spectrum (right RAW A-line cut-off)
    start_wavelength - start of wavelength range for laser
    end_wavelength - end of wavelength range for laser
    hann_flag - flag for Hanning window [3]
    dB_flag - flag for scale: linear or dB (20log())
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
    this function is experimental to test the spline interpolation + FFT for
    spectrum linear in wavelengths. Use spline_FFT.cpp file to perform spline
    interpolation + FFT for any kind of spectrum.
  
  REFERENCES:
    [1] http://www.fftw.org/fftw3_doc/Real_002dto_002dReal-Transforms.html
    [2] http://en.wikipedia.org/wiki/Spline_interpolation#Cubic_spline_interpolation
    [3] http://en.wikipedia.org/wiki/Hann_function 
*/
I8 OL_easy_spline_fft(U32 X, U32 Y, U32 start_index, U32 end_index,
                      DBL start_wavelength, DBL end_wavelength, I8 hann_flag,
                      I8 dB_flag, DBL *in, DBL *intensity, DBL *phase, DBL *Re,
                      DBL *Im) {
  U32 size = end_index - start_index;
  DBL *hann_win = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  DBL *XX = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  DBL *XXX = static_cast<DBL *>(fftw_malloc(sizeof(DBL) * size));
  // create FFTW plan
  fftw_plan fft_p = fftw_plan_r2r_1d(size, Re, Im, FFTW_R2HC, FFTW_ESTIMATE);
  U32 width = static_cast<U32>(size/2);
  // linear wavelength step
  DBL wavelength_step = (end_wavelength - start_wavelength) / (size - 1);
  DBL start_wavenumber = 1 / start_wavelength;
  // linear wavenumber step
  DBL wavenumber_step = (start_wavenumber - (1 / end_wavelength)) / (size - 1);
  I32 j;
  // prepare Hanning window and linear and non-linear wavelength vectors
  for (U32 i = 0; i < size; i++) {
    if (hann_flag)
      hann_win[i] = 0.5 * (1 - cos(kTwoPi * i / size));
    else
      hann_win[i] = 1.0;
    // linear in wavelength
    XX[i] = wavelength_step * i + start_wavelength;
    // non-linear in wavelength
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
    cubic_nak(size, XX, tmp_fft_out, b, c, d);
    // apply hanning window or just get values
    for (U32 i = 0; i < size; i++) tmp_fft_in[i] =
      hann_win[i] * spline_eval(size, XX, tmp_fft_out, b, c, d, XXX[i]);
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
  fftw_free(XX);
  fftw_free(XXX);
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
