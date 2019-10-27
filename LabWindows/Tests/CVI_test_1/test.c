/*******************************************************************************
*  $Id: test.c 115 2010-07-28 04:13:18Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include <utility.h>
#include <cvirte.h>
#include <userint.h>
#include "test.h"
#include "thread.h"

int main (int argc, char *argv[])
{
  if (InitCVIRTE (0, argv, 0) == 0)
    return -1;  /* out of memory */
  if ((panelHandle = LoadPanel (0, "test.uir", PANEL)) < 0)
    return -1;
  
  //  Create and get a thread lock.
  CmtNewLock("", 0, &lock);
  CmtGetLock (lock);
  /* Schedule thread function */
  CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, threadFunc, NULL,
    &threadId);
  
  status = 0; // run user interface
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  DisplayPanel (panelHandle);
  RunUserInterface ();
  
  /* close lock */
  CmtDiscardLock (lock);
  
  DiscardPanel (panelHandle);
  return 0;
}

int CVICALLBACK PanelCB (int panel, int event, void *callbackData,
                         int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_GOT_FOCUS:
    
      break;
    case EVENT_LOST_FOCUS:
    
      break;
    case EVENT_CLOSE:
      SetCtrlVal (panelHandle, PANEL_TEXTSTRING, "Bye! Let stop!");
      Delay (1.0);
      if (status < 1)
      {
        CmtReleaseLock (lock);
      }
      QuitUserInterface (0);
      
      break;
  }
  return 0;
}

int CVICALLBACK RunCB (int panel, int control, int event, void *callbackData,
                       int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_COMMIT:
      SetCtrlAttribute (panelHandle, PANEL_RUNBUTTON, ATTR_DIMMED, 1);
      SetCtrlVal (panelHandle, PANEL_TEXTSTRING, "Nice! Let run!");
      status = 1; // exit RunCB()
      SetCtrlVal (panelHandle, PANEL_STATUS, status);
      Delay (1.0);
      CmtReleaseLock (lock);
      
      break;
  }
  return 0;
}
