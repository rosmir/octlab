/*******************************************************************************
*  $Id: SaveCallBack.c 126 2010-08-12 02:35:13Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

int CVICALLBACK SaveCB (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_COMMIT:
      // check button STOP
      GetCtrlVal (panelHandle, PANEL_SAVESWITCH, &save);
      
      if (save == 1)
      {
        if (strcmp (pathName, "") < 1)
          BrowseCB (panel, PANEL_BROWSE, event, NULL, 0, 0);
        SetCtrlAttribute (panelHandle, PANEL_BROWSE, ATTR_DIMMED, 1);
        save = 2;
      } else {
        SetCtrlAttribute (panelHandle, PANEL_BROWSE, ATTR_DIMMED, 0);
      }

      break;
  }
  return 0;
}
