/*******************************************************************************
*  $Id: BrowseCallBack.c 126 2010-08-12 02:35:13Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

int CVICALLBACK BrowseCB (int panel, int control, int event,
    void *callbackData, int eventData1, int eventData2)
{
  switch (event)
  {
    case EVENT_COMMIT:
      while (VAL_NO_DIRECTORY_SELECTED == DirSelectPopup ("",
        "select directory to save files", 0, 1, pathName));
      SetCtrlAttribute (panelHandle, PANEL_DIRPATH, ATTR_CTRL_VAL, pathName);
      
      break;
  }
  return 0;
}
