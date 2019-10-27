/*******************************************************************************
*  $Id: ALineCallBack.c 125 2010-08-09 21:05:09Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

// get ALine index
int CVICALLBACK ALineCB (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_COMMIT:
      GetCtrlAttribute (panelHandle, PANEL_ALINEINDEX, ATTR_CTRL_VAL,
        &aLineIndex);

      break;
  }
  return 0;
}
