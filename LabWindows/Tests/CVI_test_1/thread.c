/*******************************************************************************
*  $Id: thread.c 117 2010-08-01 20:39:18Z rosmir $
*  Copyright (C) 2010 Stepan A. Baranov (stepan@baranov.su)
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "toolbox.h"
#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <cvinetv.h>
#include "test.h"
#include "thread.h"


///----------------------------------------------------------------------------
/// HIFN Network Variable Data Transferred Callback called when written data
/// HIFN is successfully received by the server.
/// HIFN NOTE: This callback is called on a worker thread and not the main thread.
/// HIPAR handle/Handle of the Network Variable connection
/// HIPAR error/The error, if any, in transferring the Network Variable data
/// HIPAR callbackData/User specified callback data
///----------------------------------------------------------------------------
static void CVICALLBACK DataTransferredCallback (void * handle, int error, 
        void * callbackData)
{
  if (error < 0)
  {
    SetCtrlVal (panelHandle, PANEL_CNVSTATUS, CNVGetErrorDescription(error));
  }
  else
  {
    SetCtrlVal (panelHandle, PANEL_LED, 1);
  }
}

///----------------------------------------------------------------------------
/// HIFN Network Variable Status Callback called whenever connection status changes.
/// HIFN NOTE: This callback is called on a worker thread and not the main thread.
/// HIPAR handle/Handle of the Network Variable connection
/// HIPAR status/The new status of the Network Variable connection
/// HIPAR error/The error, if any, in the Network Variable connection
/// HIPAR callbackData/User specified callback data
///----------------------------------------------------------------------------
static void CVICALLBACK StatusCallback (void * handle, 
        CNVConnectionStatus status, int error, void * callbackData)
{
  if (error < 0)
  {
    SetCtrlVal (panelHandle, PANEL_CNVSTATUS, CNVGetErrorDescription(error));
  }
  else
  {
    switch (status)
    {
      case CNVConnecting:
        SetCtrlVal (panelHandle, PANEL_CNVSTATUS, "Connecting...");
        break;
      case CNVConnected:
        SetCtrlVal (panelHandle, PANEL_CNVSTATUS, "Connected");
        break;
      case CNVDisconnected:
        SetCtrlVal (panelHandle, PANEL_CNVSTATUS, "Disconnected!");
        break;
    }
  }
}


int CVICALLBACK threadFunc (void *functionData)
{
  char textline[1024];
  volatile int stop = 0, loop = 0;
  double value = 0.0;
  CNVBufferedWriter    bufferedWriter;
  CNVData data = 0;
  
  int error;
  char buffer[MAX_PATHNAME_LEN];
  
  // wait for tread lock
  CmtGetLock (lock);
  // release the lock
  CmtReleaseLock (lock);
  
  status = 2; // run while loop
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  
  SetCtrlVal(panelHandle, PANEL_TEXTSTRING, "Nice! thread() has been started!");
  Delay (1.0);
  
  error = NetworkVariablePopup (buffer);
  if (error < 0)
  {
    MessagePopup ("Error", GetGeneralErrorString(error));
    return 0;
  }
  else if (error > 0)
  {
    SetCtrlVal (panelHandle, PANEL_NAME, buffer);
    SetWaitCursor (1);
    error = CNVCreateBufferedWriter (buffer, DataTransferredCallback, StatusCallback, 0, 10, 10000, 0, &bufferedWriter);
    SetWaitCursor (0);
    if (error < 0)
    {
      MessagePopup ("Error", CNVGetErrorDescription(error));
      return 0;
    }
    else
    {
      SetCtrlVal (panelHandle, PANEL_CNVSTATUS, "Connected");
    }   
  }
  
  CNVCreateScalarDataValue (&data, CNVDouble, value);
  
  while (stop == 0)
  {
    SetCtrlVal (panelHandle, PANEL_LED, 0);
    GetCtrlVal (panelHandle, PANEL_STOPBUTTON, &stop);
    Delay (0.2);
    sprintf (textline, "%i, %i", loop++, stop);
    SetCtrlVal (panelHandle, PANEL_TEXTSTRING, textline);
    value = loop;
    CNVSetScalarDataValue (data, CNVDouble, value);
    CNVPutDataInBuffer (bufferedWriter, data, CNVDoNotWait);
  }
  
  SetCtrlVal(panelHandle, PANEL_TEXTSTRING, "Nice! thread() has been stopped!");
  Delay (1.0);
  
  CNVDisposeData (data);
  CNVDispose (bufferedWriter);
  CNVFinish ();
  
  status = 3; // exit threadFunc()
  SetCtrlVal (panelHandle, PANEL_STATUS, status);
  
  return 0;
}

