/*******************************************************************************
*  $Id: lin_regr.cpp 2 2010-01-05 03:34:41Z rosmir $
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

// for DLL export
extern "C" {
DllExport I8 OL_lin_regr(U32, DBL *, DBL *, DBL *, DBL *);
}

// linear regression main function
// y=ax+b
I8 OL_lin_regr(U32 SIZE, DBL *a, DBL *b, DBL *x, DBL *y) {
  DBL s_xy = 0.0, s_x = 0.0, s_y = 0.0, s_x2 = 0.0;

  for (DBL *ptr1 = x, *ptr2 = y; ptr1 < x + SIZE; ptr1++, ptr2++) {
    s_xy = s_xy + (*ptr1) * (*ptr2);
    s_x = s_x + (*ptr1);
    s_y = s_y + (*ptr2);
    s_x2 = s_x2 + (*ptr1) * (*ptr1);
  }

  *b = (SIZE * s_xy - s_x * s_y) / (SIZE * s_x2 - s_x * s_x);
  *a = (s_y - *b * s_x) / SIZE;
  return EXIT_SUCCESS;
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
