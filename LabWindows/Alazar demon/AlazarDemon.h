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
#define  PANEL_TIMEVALUE                  2       /* control type: numeric, callback function: (none) */
#define  PANEL_MAXFRAMES                  3       /* control type: numeric, callback function: (none) */
#define  PANEL_DATALOOPS                  4       /* control type: numeric, callback function: (none) */
#define  PANEL_MAXMEMORY                  5       /* control type: numeric, callback function: (none) */
#define  PANEL_ALAZARLOOPS                6       /* control type: numeric, callback function: (none) */
#define  PANEL_BUFFERSIZE                 7       /* control type: numeric, callback function: (none) */
#define  PANEL_MAXSAMPLESPERCHANNEL       8       /* control type: numeric, callback function: (none) */
#define  PANEL_BYTESPERSAMPLE             9       /* control type: numeric, callback function: (none) */
#define  PANEL_RUNBUTTON                  10      /* control type: command, callback function: RunCB */
#define  PANEL_CLOCKSOURCE                11      /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLERATE                 12      /* control type: ring, callback function: (none) */
#define  PANEL_CLOCKEDGE                  13      /* control type: ring, callback function: (none) */
#define  PANEL_REFERENCECHANNEL           14      /* control type: ring, callback function: (none) */
#define  PANEL_SAMPLECHANNEL              15      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGEXTTRIG            16      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGREFCH              17      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGEREFCH            18      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUEREFCH              19      /* control type: ring, callback function: (none) */
#define  PANEL_COUPLINGSAMPLECH           20      /* control type: ring, callback function: (none) */
#define  PANEL_INPUTRANGESAMPLECH         21      /* control type: ring, callback function: (none) */
#define  PANEL_IMPVALUESAMPLECH           22      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINEOP               23      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE2                24      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE2                25      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL2                 26      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE2                 27      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGENGINE1                28      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGSOURCE1                29      /* control type: ring, callback function: (none) */
#define  PANEL_TRIGLEVEL1                 30      /* control type: numeric, callback function: (none) */
#define  PANEL_TRIGSLOPE1                 31      /* control type: ring, callback function: (none) */
#define  PANEL_RANGEIDEXTTRIG             32      /* control type: ring, callback function: (none) */
#define  PANEL_MODE                       33      /* control type: ring, callback function: (none) */
#define  PANEL_STOPBUTTON                 34      /* control type: textButton, callback function: StopCB */
#define  PANEL_STATUS                     35      /* control type: numeric, callback function: (none) */
#define  PANEL_RAWBLINESIZE               36      /* control type: numeric, callback function: (none) */
#define  PANEL_ALINEINDEX                 37      /* control type: numeric, callback function: ALineCB */
#define  PANEL_RAWALINESIZE               38      /* control type: numeric, callback function: (none) */
#define  PANEL_ERRORMSG                   39      /* control type: textBox, callback function: (none) */
#define  PANEL_ALINEGRAPH                 40      /* control type: graph, callback function: (none) */
#define  PANEL_SAVESWITCH                 41      /* control type: binary, callback function: SaveCB */
#define  PANEL_CHANNELSWITCH              42      /* control type: binary, callback function: ChannelCB */
#define  PANEL_DIRPATH                    43      /* control type: string, callback function: (none) */
#define  PANEL_BROWSE                     44      /* control type: command, callback function: BrowseCB */
#define  PANEL_LED                        45      /* control type: LED, callback function: (none) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ALineCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BrowseCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChannelCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
