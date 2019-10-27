/*******************************************************************************
*  $Id: AlazarAcquire.c 127 2010-08-12 20:32:25Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

// thread to acquire Alazar card
int CVICALLBACK AlazarAcquire (void *functionData)
{
  char textLine[4096];
  BOOL success = TRUE;
  RETURN_CODE retCode;
  U32 timeout_ms = 5000;
  double initialTime = 0.0;
  BOOL isFull = FALSE;
  
  // wait for tread lock
  CmtGetLock (alazarThreadLock);
  // release the lock
  CmtReleaseLock (alazarThreadLock);
  
  // create buffer
  FIFOBuff = (fifo_t *) malloc (sizeof (fifo_t));
  FIFOBuff->f_head = NULL;
  FIFOBuff->f_tail = NULL;
  
  // set status
  status = 2; // AlazarAcquire is started
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! AlazarAcquire() has been started!\n");
  
  // Arm the board to begin acquisition
  retCode = AlazarStartCapture (boardHandle);
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,
      "Error: AlazarStartCapture failed -- %s\n", AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    success = FALSE;
    return FALSE;
  }
  
  // init the values
  alazarLoop = 0;
  initialTime = Timer ();
  
  // run until button STOP pressed
  while (stop == 0)
  {
    // get the time
    double tempTime = Timer ();
    
    // wait for new Alazar card buffer
    retCode = AlazarWaitNextAsyncBufferComplete (
      boardHandle,
      frameBuffer,
      bytesPerBuffer,
      timeout_ms
      );
    if (retCode == ApiSuccess) // everything is ok
    {
      // pulsed mode of FIFO buffer adding
      if (! isFull)
      {
        if (save == 2) alazarLoop++;
        // add acquired buffer to FIFO buffer and recreate memory space for next
        // buffer from Alazar card. After that notify DataThread() through event
        FIFO_Add (FIFOBuff, frameBuffer);
        frameBuffer = NULL;
        // allocate memory for the next buffer from Alazar card
        frameBuffer = (U16 *) malloc (bytesPerBuffer);
        if ((alazarLoop - dataLoop) > maxNumOfFrames)
        {
          status = 4; // Alazar stopped to update FIFO queue
          SetCtrlVal (panelHandle, PANEL_STATUS, status);
          isFull = TRUE;
          SetCtrlVal (panelHandle, PANEL_LED, isFull);
        }
      }
      
      SetEvent (eventData); // DataThread() can run now
      timerValue = tempTime - initialTime; // calculate time period for current
                                           // loop
      initialTime = tempTime;              // remember time value for next
                                           // iteration
    }
    else if (retCode == ApiTransferComplete) // we never come here but reserve 
                                             // for future use
    {
      // This buffer is full, and it's the last buffer in the acquisition
    }
    else // Ooops! we have error!
    {
      sprintf (textLine,
        "Error: AlazarWaitNextAsyncBufferComplete failed -- %s\n",
        AlazarErrorToText(retCode));
      SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
      Delay (5.0);
      return FALSE;
    }
  }
  
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! AlazarAcquire() has been stopped!\n");
  
  return 0;
}
