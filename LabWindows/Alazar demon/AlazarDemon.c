/*******************************************************************************
*  $Id: AlazarDemon.c 126 2010-08-12 02:35:13Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

// main thread that asists UI
int main (int argc, char *argv[])
{
  // load UI panel
  if (InitCVIRTE (0, argv, 0) == 0)
    return -1;  /* out of memory */
  if ((panelHandle = LoadPanel (0, "AlazarDemon.uir", PANEL)) < 0)
    return -1;
  
  // Create and get a thread locks
  // for AlazarAcquire() thread.
  CmtNewLock ("", 0, &alazarThreadLock);
  CmtGetLock (alazarThreadLock);
  // for DataThread() thread
  CmtNewLock ("", 0, &dataThreadLock);
  CmtGetLock (dataThreadLock);
  
  // init values
  stop = 0;
  save = 0;
  channel = 0;
  strcpy (pathName, "");
  
  // create Windows Event variable
  eventData = CreateEvent (NULL, FALSE, FALSE, NULL);
    
  /* Schedule thread functions */
  CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AlazarAcquire,
    NULL, &alazarThreadId);
  CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, DataThread, NULL,
    &dataThreadId);
  
  // set status
  status = 0; // run user interface
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  
  // run UI
  DisplayPanel (panelHandle);
  RunUserInterface ();
  
  // close UI
  DiscardPanel (panelHandle);
  CloseCVIRTE ();
  return 0;
}

// quit UI
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
      stop = 1;
      SetCtrlVal (panelHandle, PANEL_ERRORMSG, "Bye! Let stop!\n");
      Delay (1.0);
      QuitUserInterface (0);

      break;
  }
  return 0;
}

// run application
int CVICALLBACK RunCB (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_COMMIT:
      
      // prevent from second run
      SetCtrlAttribute (panelHandle, PANEL_RUNBUTTON, ATTR_DIMMED, 1);
      
      // get number of Alazar card systems
      if (1 != AlazarNumOfSystems ()) {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "Ooops! The number of systems is not equal to 1!\n");
        return 0;
      }
      
      // get number of boards within first system
      if (1 != AlazarBoardsInSystemBySystemID (1)) {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "Ooops! The number of boards is not equal to 1!\n");
        return 0;
      }
      
      // Get a handle to the first board of first system
      boardHandle = AlazarGetBoardBySystemID (1, 1);
      if (boardHandle == NULL) {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "Ooops! Could not get the handle for board!\n");
        return 0;
      } else {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "Nice! The board handle is ok!\n");
      }
      
      // Toggle the LED on the board’s PCI/PCIe mounting bracket
      AlazarSetLED (boardHandle, LED_ON);
      Delay (0.5);
      AlazarSetLED (boardHandle, LED_OFF);
      
      // init the board
      if (! AlazarInit ())
      {
        SetCtrlVal (panelHandle, PANEL_ERRORMSG,
          "Ooops! The AlazarInit() failed!\n");
        return 0;
      }
      
      // set status
      status = 1; // exit RunCB()
      SetCtrlVal (panelHandle, PANEL_STATUS, status);
      // unfreeze AlazarAcquire() thread
      CmtReleaseLock (alazarThreadLock);
      // unfreeze DataThread() thread
      Delay (0.1);
      CmtReleaseLock (dataThreadLock);

      break;
  }
  return 0;
}
