/*******************************************************************************
*  $Id: rsmfifo.h 122 2010-08-05 17:48:01Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#ifndef __RSMFIFO_H__
#define __RSMFIFO_H__

#ifdef __cplusplus
  extern "C" {
#endif

typedef struct fifonode_ {
  void *fn_data;
  struct fifonode_ *fn_next;
} fifonode_t;

typedef struct fifo_ {
  fifonode_t *f_head;
  fifonode_t *f_tail;
} fifo_t;

fifo_t *FIFOBuff; /* global FIFO buffer */

int errCnt; /* error counter for FIFO buffer */

#ifdef __cplusplus
  }
#endif

#endif  /* ndef __RSMFIFO_H__ */
