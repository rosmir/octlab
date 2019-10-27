/*******************************************************************************
*  $Id: peak_width.cpp 14 2010-01-08 04:47:37Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// standard header
#include <numeric>
// common header
#include "./OCTLib.h"

// for DLL export
extern "C" {
DllExport DBL OL_peak_width(U32, DBL *, DBL *);
}

// peak width (weighted variance) main function
DBL OL_peak_width(U32 SIZE, DBL *ptr1, DBL *ptr2) {
  DBL tmp = 0.0;
  DBL sum = accumulate(ptr2, ptr2 + SIZE, 0.0);
  DBL mean = inner_product(ptr2, ptr2 + SIZE, ptr1, 0.0) / sum;
  DBL sum2 = 0.0;

  for (DBL *t1 = ptr1, *t2 = ptr2; t1 < ptr1 + SIZE; t1++, t2++) {
    tmp = tmp + (*t1 - mean) * (*t1 - mean) * (*t2);
    sum2 = sum2 + (*t2) * (*t2);
  }

  return sqrt(tmp * sum / (sum * sum - sum2));
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
