/*******************************************************************************
*  $Id: DataThread.c 127 2010-08-12 20:32:25Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

int CVICALLBACK DataThread (void *functionData)
{
  char fileNameA[32];
  char fileNameB[32];
  char filePathA[MAX_PATHNAME_LEN]; // for data from channel A
  char filePathB[MAX_PATHNAME_LEN]; // for data from channel B
  U16 *data;
  FILE *outA, *outB;
  unsigned int numberOfElements = 0;
  
  // wait for tread lock
  CmtGetLock (dataThreadLock);
  // release the lock
  CmtReleaseLock (dataThreadLock);
  
  status = 3; // DataThread() is started
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been started!\n");
  
  // get the total number of elements to write
  numberOfElements = rawBscanSize * rawAlineSize;
  
  // init the values
  dataLoop = 0;
  
  // run until button STOP pressed
  while (stop == 0)
  {
    // wait for event from AlazarAcquire()
    WaitForSingleObject (eventData, INFINITE);
    
    // remove buffer from FIFO buffer and free memory space
    while (FIFOBuff->f_head != FIFOBuff->f_tail)
    {
      data = FIFO_Remove (FIFOBuff); // remove buffer from FIFO queue
      // update counters
      SetCtrlAttribute (panelHandle, PANEL_TIMEVALUE, ATTR_CTRL_VAL,
        timerValue * 1000.0);
      
      // draw plot
      DeleteGraphPlot (panelHandle, PANEL_ALINEGRAPH, -1, VAL_DELAYED_DRAW);
      PlotY (panelHandle, PANEL_ALINEGRAPH,
        data + numberOfElements * channel + rawAlineSize * aLineIndex,
        rawAlineSize, VAL_UNSIGNED_SHORT_INTEGER, VAL_FAT_LINE,
        VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_CYAN);
      
      // record files only if we have directory name in pathName variable
      if ((save == 2) || (dataLoop < alazarLoop))
      {
        // set number of buffers which were saved
        SetCtrlAttribute (panelHandle, PANEL_DATALOOPS, ATTR_CTRL_VAL,
          dataLoop++);
        SetCtrlAttribute (panelHandle, PANEL_ALAZARLOOPS, ATTR_CTRL_VAL,
          alazarLoop);
        // set the name of output files and notify
        sprintf (fileNameA, "%09lli.mzi.raw.dat", dataLoop);
        sprintf (fileNameB, "%09lli.sample.raw.dat", dataLoop);
        MakePathname (pathName, fileNameA, filePathA);
        MakePathname (pathName, fileNameB, filePathB);
        SetCtrlAttribute (panelHandle, PANEL_DIRPATH, ATTR_CTRL_VAL, filePathB);
        // open output files for recording
        outA = fopen (filePathA, "wb");
        outB = fopen (filePathB, "wb");
        // error handling
        if ((outA == NULL) || (outB == NULL))
        {
          SetCtrlVal (panelHandle, PANEL_ERRORMSG,
            "Ooops! We could not open files for recording!\n");
          save = 0;
          SetCtrlVal (panelHandle, PANEL_SAVESWITCH, save);
          break;
        }
        // record buffer from channel A
        if (numberOfElements != fwrite (data, bytesPerSample, numberOfElements,
          outA))
        {
          SetCtrlVal (panelHandle, PANEL_ERRORMSG,
            "Ooops! We could not write the file!\n");
          save = 0;
          SetCtrlVal (panelHandle, PANEL_SAVESWITCH, save);
          fclose (outA);
          break;
        }
        // record buffer from channel B
        if (numberOfElements != fwrite (data + numberOfElements, bytesPerSample,
          numberOfElements, outB))
        {
          SetCtrlVal (panelHandle, PANEL_ERRORMSG,
            "Ooops! We could not write the file!\n");
          save = 0;
          SetCtrlVal (panelHandle, PANEL_SAVESWITCH, save);
          fclose (outB);
          break;
        }
        // close output files
        fclose (outA);
        fclose (outB);
      }  
      
      free (data); // free buffer obtained from FIFO queue
    }
    
  }
  
  SetCtrlVal (panelHandle, PANEL_ERRORMSG,
    "Nice! DataThread() has been stopped!\n");
  
  return 0;
}
