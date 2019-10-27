/*******************************************************************************
*  $Id: thread.h 115 2010-07-28 04:13:18Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#ifndef __thread_H__
#define __thread_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

int panelHandle;
CmtThreadLockHandle lock;
int threadId;
int status;

//==============================================================================
// Global functions

int CVICALLBACK threadFunc (void *);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __thread_H__ */
