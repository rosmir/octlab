/*******************************************************************************
*  $Id: RSMFIFO.c 125 2010-08-09 21:05:09Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

// FIFO functions
// Add to the end of the FIFO buffer
void FIFO_Add (fifo_t *f, void *data)
{
  fifonode_t *fn;
  
  fn = (fifonode_t *) malloc (sizeof (fifonode_t));
  fn->fn_data = data;
  fn->fn_next = NULL;
  
  if (f->f_tail == NULL)
    {
      f->f_head = f->f_tail = fn;
      if (errCnt++)
      {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "FIFO buffer has no elements!\n");
      }
    } else {
      f->f_tail->fn_next = fn;
      f->f_tail = fn;
    }
}

// Remove from the front of the FIFO buffer
void * FIFO_Remove (fifo_t *f)
{
    fifonode_t *fn;
    void *data;
  
    if ((fn = f->f_head) == NULL)
      return (NULL);
  
    data = fn->fn_data;
    if ((f->f_head = fn->fn_next) == NULL)
      f->f_tail = NULL;
  
    free (fn);
    return (data);
}
