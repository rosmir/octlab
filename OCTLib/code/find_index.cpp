/*******************************************************************************
*  $Id: find_index.cpp 14 2010-01-08 04:47:37Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

// standard header
#include <map>
// common header
#include "./OCTLib.h"

I32 find_index(map<DBL, I32> *spectrum_map, DBL key) {
  map<DBL, I32>::iterator spectrum_p = spectrum_map->lower_bound(key);
  return (spectrum_p->second - 1);
}

/*******************************************************************************
Checked by http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
*******************************************************************************/
