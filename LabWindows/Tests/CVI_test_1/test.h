/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2010. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: PanelCB */
#define  PANEL_RUNBUTTON                  2       /* control type: command, callback function: RunCB */
#define  PANEL_TEXTSTRING                 3       /* control type: string, callback function: (none) */
#define  PANEL_STOPBUTTON                 4       /* control type: textButton, callback function: (none) */
#define  PANEL_STATUS                     5       /* control type: numeric, callback function: (none) */
#define  PANEL_NAME                       6       /* control type: string, callback function: (none) */
#define  PANEL_CNVSTATUS                  7       /* control type: string, callback function: (none) */
#define  PANEL_LED                        8       /* control type: LED, callback function: (none) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
