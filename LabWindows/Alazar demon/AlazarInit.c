/*******************************************************************************
*  $Id: AlazarInit.c 126 2010-08-12 02:35:13Z rosmir $
*  Copyright (C) 2010 OCTLab Project
*  All rights reserved.
*  web-site: www.OCTLab.org
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

#include "AlazarThread.h"

// initialize Alazar card
BOOL AlazarInit (void)
{
  RETURN_CODE retCode; // return code for native Alazar functions
  char textLine[4096]; // variable for text messages

  // local variables
  U32 clockSource = 0;
  U32 sampleRate = 0;
  U32 clockEdge = 0;
  U8 sampleChannel = 0;
  U8 referenceChannel = 0;
  U32 couplingSampleChannel = 0;
  U32 inputRangeSampleChannel = 0;
  U32 impdenceValueSampleChannel = 0;
  U32 couplingReferenceChannel = 0;
  U32 inputRangeReferenceChannel = 0;
  U32 impdenceValueReferenceChannel = 0;
  U32 triggerEngineOperation=0;
  U32 triggerEngineId1 = 0;
  U32 triggerSourceId1 = 0;
  U32 triggerLevel1 = 0;
  U32 triggerSlope1 = 0;
  U32 triggerEngineId2 = 0;
  U32 triggerSourceId2 = 0;
  U32 triggerLevel2 = 0;
  U32 triggerSlope2 = 0;
  U32 couplingExternalTrigger = 0;
  U32 rangeIdExternalTrigger = 0;
  U32 mode = 0;
  U32 recordsPerAcquisition = 0;
  U32 admaFlags = 0;
  U32 channelMask = 0;
  U32 triggerDelay = 0;
  U32 triggerTimeout = 0;
  U8 bitsPerSample;
  U32 maxSamplesPerChannel;
  BOOL success = TRUE;
  size_t availablePhysical = 0;
  
  // Configure sample clock source, edge, and decimation
  GetCtrlAttribute (panelHandle, PANEL_CLOCKSOURCE, ATTR_CTRL_VAL, &clockSource);
  SetCtrlAttribute (panelHandle, PANEL_CLOCKSOURCE, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_SAMPLERATE, ATTR_CTRL_VAL, &sampleRate);
  SetCtrlAttribute (panelHandle, PANEL_SAMPLERATE, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_CLOCKEDGE, ATTR_CTRL_VAL, &clockEdge);
  SetCtrlAttribute (panelHandle, PANEL_CLOCKEDGE, ATTR_DIMMED, 1);
  retCode = 
    AlazarSetCaptureClock (
      boardHandle,      // HANDLE -- board handle
      clockSource,      // U32 -- clock source id
      sampleRate,       // U32 -- sample rate id
      clockEdge,        // U32 -- clock edge id
      0                 // U32 -- clock decimation 
      );                  
  if (retCode != ApiSuccess)
  {
    sprintf (textLine, "Error: AlazarSetCaptureClock failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }
  
  // Select the input coupling, range, and impedance of a digitizer sample
  // channel
  GetCtrlAttribute (panelHandle, PANEL_SAMPLECHANNEL, ATTR_CTRL_VAL,
    &sampleChannel);
  SetCtrlAttribute (panelHandle, PANEL_SAMPLECHANNEL, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_COUPLINGSAMPLECH, ATTR_CTRL_VAL,
    &couplingSampleChannel);
  SetCtrlAttribute (panelHandle, PANEL_COUPLINGSAMPLECH, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_INPUTRANGESAMPLECH, ATTR_CTRL_VAL,
    &inputRangeSampleChannel);
  SetCtrlAttribute (panelHandle, PANEL_INPUTRANGESAMPLECH, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_IMPVALUESAMPLECH, ATTR_CTRL_VAL,
    &impdenceValueSampleChannel);
  SetCtrlAttribute (panelHandle, PANEL_IMPVALUESAMPLECH, ATTR_DIMMED, 1);
  retCode = 
    AlazarInputControl (
      boardHandle,                   // HANDLE -- board handle
      sampleChannel,                 // U8 -- input channel 
      couplingSampleChannel,         // U32 -- input coupling id
      inputRangeSampleChannel,       // U32 -- input range id
      impdenceValueSampleChannel     // U32 -- input impedance id
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine, "Error: AlazarInputControl failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Control bandwidth of an input sample channel
  retCode = 
    AlazarSetBWLimit (
      boardHandle,      // HANDLE -- board handle
      sampleChannel,    // U8 -- channel identifier
      0                 // U32 -- 0 = disable, 1 = enable
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetBWLimit failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Select the input coupling, range, and impedance of a digitizer reference
  // channel 
  GetCtrlAttribute (panelHandle, PANEL_REFERENCECHANNEL, ATTR_CTRL_VAL,
    &referenceChannel);
  SetCtrlAttribute (panelHandle, PANEL_REFERENCECHANNEL, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_COUPLINGREFCH, ATTR_CTRL_VAL,
    &couplingReferenceChannel);
  SetCtrlAttribute (panelHandle, PANEL_COUPLINGREFCH, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_INPUTRANGEREFCH, ATTR_CTRL_VAL,
    &inputRangeReferenceChannel);
  SetCtrlAttribute (panelHandle, PANEL_INPUTRANGEREFCH, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_IMPVALUEREFCH, ATTR_CTRL_VAL,
    &impdenceValueReferenceChannel);
  SetCtrlAttribute (panelHandle, PANEL_IMPVALUEREFCH, ATTR_DIMMED, 1);
  retCode = 
    AlazarInputControl (
      boardHandle,                  // HANDLE -- board handle
      referenceChannel,             // U8 -- channel identifier
      couplingReferenceChannel,     // U32 -- input coupling id
      inputRangeReferenceChannel,   // U32 -- input range id
      impdenceValueReferenceChannel // U32 -- input impedance id
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarInputControl failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Control bandwidth of an input reference channel
  retCode = 
    AlazarSetBWLimit (
      boardHandle,           // HANDLE -- board handle
      referenceChannel,      // U8 -- channel identifier
      0                      // U32 -- 0 = disable, 1 = enable
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetBWLimit failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }
  
  // Configure the trigger system
  GetCtrlAttribute (panelHandle, PANEL_TRIGENGINEOP, ATTR_CTRL_VAL,
    &triggerEngineOperation);
  SetCtrlAttribute (panelHandle, PANEL_TRIGENGINEOP, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGENGINE1, ATTR_CTRL_VAL,
    &triggerEngineId1);
  SetCtrlAttribute (panelHandle, PANEL_TRIGENGINE1, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGSOURCE1, ATTR_CTRL_VAL,
    &triggerSourceId1);
  SetCtrlAttribute (panelHandle, PANEL_TRIGSOURCE1, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGLEVEL1, ATTR_CTRL_VAL,
    &triggerLevel1);
  SetCtrlAttribute (panelHandle, PANEL_TRIGLEVEL1, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGSLOPE1, ATTR_CTRL_VAL,
    &triggerSlope1);
  SetCtrlAttribute (panelHandle, PANEL_TRIGSLOPE1, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGENGINE2, ATTR_CTRL_VAL,
    &triggerEngineId2);
  SetCtrlAttribute (panelHandle, PANEL_TRIGENGINE2, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGSOURCE2, ATTR_CTRL_VAL,
    &triggerSourceId2);
  SetCtrlAttribute (panelHandle, PANEL_TRIGSOURCE2, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGLEVEL2, ATTR_CTRL_VAL,
    &triggerLevel2);
  SetCtrlAttribute (panelHandle, PANEL_TRIGLEVEL2, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_TRIGSLOPE2, ATTR_CTRL_VAL,
    &triggerSlope2);
  SetCtrlAttribute (panelHandle, PANEL_TRIGSLOPE2, ATTR_DIMMED, 1);
  retCode = 
    AlazarSetTriggerOperation (
      boardHandle,              // HANDLE -- board handle
      triggerEngineOperation,   // U32 -- trigger operation 
      triggerEngineId1,         // U32 -- trigger engine id
      triggerSourceId1,         // U32 -- trigger source id
      triggerSlope1,            // U32 -- trigger slope id
      triggerLevel1,            // U32 -- trigger level from 0 (-range) to 255 
                                //        (+range)
      triggerEngineId2,         // U32 -- trigger engine id
      triggerSourceId2,         // U32 -- trigger source id for engine K
      triggerSlope2,            // U32 -- trigger slope id
      triggerLevel2             // U32 -- trigger level from 0 (-range) to 255
                                //        (+range)
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetTriggerOperation failed -- %s\n",
        AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }
  
  // Set the external trigger range and coupling.
  GetCtrlAttribute (panelHandle, PANEL_COUPLINGEXTTRIG, ATTR_CTRL_VAL,
    &couplingExternalTrigger);
  SetCtrlAttribute (panelHandle, PANEL_COUPLINGEXTTRIG, ATTR_DIMMED, 1);
  GetCtrlAttribute (panelHandle, PANEL_RANGEIDEXTTRIG, ATTR_CTRL_VAL,
    &rangeIdExternalTrigger);
  SetCtrlAttribute (panelHandle, PANEL_RANGEIDEXTTRIG, ATTR_DIMMED, 1);
  retCode =
    AlazarSetExternalTrigger ( 
      boardHandle,                // HANDLE -- board handle
      couplingExternalTrigger,    // U32 -- external trigger coupling id
      rangeIdExternalTrigger      // U32 -- external trigger range id
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetExternalTrigger failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Set the time, in sample clocks, to wait after receiving a trigger event
  // before capturing a record for the trigger. 
  retCode = AlazarSetTriggerDelay (boardHandle, triggerDelay);
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetTriggerDelay failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Set the time to wait for a trigger event before automatically generating a
  // trigger event
  retCode = 
    AlazarSetTriggerTimeOut (
      boardHandle,        // HANDLE -- board handle
      triggerTimeout      // U32 -- timeout_sec / 10.e-6 (0 means wait forever)
      );
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarSetTriggerTimeOut failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }

  // Configure the AUX I/O connector as an input or output signal
  GetCtrlAttribute (panelHandle, PANEL_MODE, ATTR_CTRL_VAL, &mode);
  SetCtrlAttribute (panelHandle, PANEL_MODE, ATTR_DIMMED, 1);
  retCode = 
    AlazarConfigureAuxIO (
      boardHandle,            // HANDLE -- board handle
      mode,                   // U32 -- mode
      TRIGGER_SLOPE_NEGATIVE  // U32 -- parameter
      );  
  if (retCode != ApiSuccess)
  {
    sprintf (textLine,"Error: AlazarConfigureAuxIO failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }
  
  // get raw a-line size
  GetCtrlAttribute (panelHandle, PANEL_RAWALINESIZE, ATTR_CTRL_VAL,
    &rawAlineSize);
  SetCtrlAttribute (panelHandle, PANEL_RAWALINESIZE, ATTR_DIMMED, 1);
  
  // Get the on-board memory in samples per channel, and sample size in bits
  // per sample
  retCode = AlazarGetChannelInfo (boardHandle, &maxSamplesPerChannel,
    &bitsPerSample);
  if (retCode!= ApiSuccess)
  { 
    sprintf (textLine,"Error: AlazargetChannelInfo failed -- %s\n",
      AlazarErrorToText(retCode));
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    return FALSE;
  }
  SetCtrlAttribute (panelHandle, PANEL_MAXSAMPLESPERCHANNEL, ATTR_CTRL_VAL,
    maxSamplesPerChannel);
  
  // get the size of each sample in bytes
  bytesPerSample = (bitsPerSample + 7)/8;
  SetCtrlAttribute (panelHandle, PANEL_BYTESPERSAMPLE, ATTR_CTRL_VAL,
    bytesPerSample);
  
  // get number of A-lines in a B-scan
  GetCtrlAttribute (panelHandle, PANEL_RAWBLINESIZE, ATTR_CTRL_VAL,
    &rawBscanSize);
  SetCtrlAttribute (panelHandle, PANEL_RAWBLINESIZE, ATTR_DIMMED, 1);
  
  // limit the number of A-lines for PANEL_ALINEINDEX control
  SetCtrlAttribute (panelHandle, PANEL_ALINEINDEX, ATTR_MAX_VALUE,
    rawBscanSize - 1);
  
  // check that B-scan fits on-board memory
  if ((rawAlineSize * rawBscanSize) > maxSamplesPerChannel)
  {
    SetCtrlVal (panelHandle, PANEL_ERRORMSG,
      "B-scan size does not fit the on-board memory!\n");
    return FALSE;
  }
  
  // Calculate Bytes per Buffer, for 2 channels
  bytesPerBuffer = rawAlineSize * rawBscanSize * bytesPerSample * 2;
  if ((bytesPerBuffer % 32) != 0) {
    SetCtrlVal (panelHandle, PANEL_ERRORMSG,
      "The number of samples is not order of 32\n");
    return FALSE;
  }
  SetCtrlAttribute (panelHandle, PANEL_BUFFERSIZE, ATTR_CTRL_VAL,
    bytesPerBuffer);
  
  // Allocate memory for DMA buffers
  success = TRUE;
  frameBuffer = (U16 *) malloc (bytesPerBuffer);
  if (frameBuffer == NULL)
  {
    sprintf (textLine, "Error: alloc %d bytes failed\n", bytesPerBuffer);
    SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
    success = FALSE;
    return FALSE;
  }
  
  // get amount of RAM available for application
  GetMemoryInfo (NULL, NULL, NULL, NULL, &availablePhysical, NULL, NULL);
  SetCtrlVal (panelHandle, PANEL_MAXMEMORY,
    (double)availablePhysical/1073741824);
  
  // get maximum number of buffers inside FIFO queue
  maxNumOfFrames = (U32)(0.7 * (double)availablePhysical/bytesPerBuffer);
  SetCtrlVal (panelHandle, PANEL_MAXFRAMES, maxNumOfFrames);
  
  // Set the number of pre- and post-trigger samples per record
  if (success)
  {
    retCode =
      AlazarSetRecordSize (
      boardHandle,       // HANDLE -- Board handle
      0,                 // U32 -- pre-trigger samples
      rawAlineSize       // U32 -- post-trigger samples
      );
    if (retCode != ApiSuccess)
    {
       sprintf (textLine, "Error: AlazarSetRecordSize failed -- %s\n",
         AlazarErrorToText(retCode));
       SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
       success = FALSE;
       return FALSE;
    }
  }
  
  // Configure a board to make an asynchronous AutoDMA acquisition
  if (success)
  {
    recordsPerAcquisition = 0x7fffffff;      // For infinitive acquisition,
                                             // acquires until acquisition is 
                                             // aborted
    admaFlags = ADMA_EXTERNAL_STARTCAPTURE | // Start Acquisition when 
                                             // AlalzarStartCapture is called
                ADMA_NPT |                   // Acquire multiple records with
                                             // no-pretrigger samples
                ADMA_ALLOC_BUFFERS;          // Allow API to allocate and manage
                                             // DMA buffers and copy data into
                                             // buffer
    channelMask = CHANNEL_A | CHANNEL_B;     // Two channels acquisition
       
    retCode = 
      AlazarBeforeAsyncRead (
        boardHandle,            // HANDLE -- Board handle
        channelMask,            // U32 -- enabled channel mask
        0,                      // Pre-trigger samples
        rawAlineSize,           // U32 -- samples per record
        rawBscanSize,           // U32 -- records per buffer
        recordsPerAcquisition,  // U32 -- records per acquisition
        admaFlags               // U32 -- AutoDMA flags
        );
    if (retCode != ApiSuccess)
    {
      sprintf (textLine, "Error: AlazarBeforeAsyncRead failed -- %s\n",
        AlazarErrorToText(retCode));
      SetCtrlVal (panelHandle, PANEL_ERRORMSG, textLine);
      success = FALSE;
      return FALSE;
    }
  }
  
  return TRUE;
}
