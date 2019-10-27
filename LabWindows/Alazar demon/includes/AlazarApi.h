#ifndef _ALAZARAPI_H
#define _ALAZARAPI_H
//=============================================================================
//
// Alazar Technologies Inc
//
//  File Name:
//
//      AlazarApi.h
//
// Copyright (c) 2006 Alazar Technologies Inc. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States And Canada.
//
// This product contains confidential information and trade secrets
// of Alazar Technologies Inc. Use, disclosure, or reproduction is
// prohibited without the prior express written permission of Alazar
// Technologies Inc
//
// Description:
//
//      API used for Alazar Acquisition Products
//
// Revision History:
//
//=============================================================================

#ifdef __cplusplus
extern "C" {
#endif

#include "AlazarError.h"

/******************************************
 *      Windows Type Definitions
 ******************************************/
//#if defined(_WIN32)
    typedef signed char      S8,  *PS8;
    typedef unsigned char    U8,  *PU8;
    typedef signed short     S16, *PS16;
    typedef unsigned short   U16, *PU16;
    typedef signed long      S32, *PS32;
    typedef unsigned long    U32, *PU32;
    typedef signed __int64    S64, *PS64;
	typedef unsigned __int64  U64, *PU64;
	typedef void *			 HANDLE;
//#endif

typedef enum BoardTypes { 
	ATS_NONE,  // NO BOARD WAS FOUND
	ATS850, 
	ATS310, 
	ATS330,
	ATS855,
	ATS315,
	ATS335,
	ATS460,
	ATS860,
	ATS660,
	ATS665,
	ATS9462,
	ATS9434,
	ATS9870,
	ATS9350,
	ATS_LAST 
}ALAZAR_BOARDTYPES;

// Board Definition structure
typedef struct _BoardDef
{
    U32 RecordCount;
    U32 RecLength;
    U32 PreDepth;
    U32 ClockSource;
    U32 ClockEdge;
    U32 SampleRate;
    U32 CouplingChanA;
    U32 InputRangeChanA;
    U32 InputImpedChanA;
    U32 CouplingChanB;
    U32 InputRangeChanB;
    U32 InputImpedChanB;
    U32 TriEngOperation;
    U32 TriggerEngine1;
    U32 TrigEngSource1;
    U32 TrigEngSlope1;
    U32 TrigEngLevel1;
    U32 TriggerEngine2;
    U32 TrigEngSource2;
    U32 TrigEngSlope2;
    U32 TrigEngLevel2;
}BoardDef, *pBoardDef;

// Constants to be used in the Application when dealing with Custom FPGAs
#define FPGA_GETFIRST	0xFFFFFFFF
#define FPGA_GETNEXT	0xFFFFFFFE
#define FPGA_GETLAST	0xFFFFFFFC
RETURN_CODE AlazarGetOEMFPGAName(int opcodeID, char *FullPath, unsigned long *error);
RETURN_CODE AlazarOEMSetWorkingDirectory(char *wDir, unsigned long *error);
RETURN_CODE AlazarOEMGetWorkingDirectory(char *wDir, unsigned long *error);
RETURN_CODE AlazarParseFPGAName(const char *FullName, char *Name, U32 *Type, U32 *MemSize, U32 *MajVer, U32 *MinVer, U32 *MajRev, U32 *MinRev, U32 *error);
RETURN_CODE AlazarOEMDownLoadFPGA( HANDLE h,char *FileName,U32 *RetValue);
RETURN_CODE AlazarDownLoadFPGA( HANDLE h,char *FileName,U32 *RetValue);

// ********************************************************************
// Header Constants and Structures that need to be used 
// when dealing with ADMA captures that use the header.
// ********************************************************************
#define ADMA_CLOCKSOURCE		0x00000001
#define ADMA_CLOCKEDGE			0x00000002
#define ADMA_SAMPLERATE			0x00000003
#define ADMA_INPUTRANGE			0x00000004
#define ADMA_INPUTCOUPLING		0x00000005
#define ADMA_IMPUTIMPEDENCE		0x00000006
#define ADMA_EXTTRIGGERED		0x00000007
#define ADMA_CHA_TRIGGERED		0x00000008
#define ADMA_CHB_TRIGGERED		0x00000009
#define ADMA_TIMEOUT			0x0000000A
#define ADMA_THISCHANTRIGGERED	0x0000000B
#define ADMA_SERIALNUMBER		0x0000000C
#define ADMA_SYSTEMNUMBER		0x0000000D
#define ADMA_BOARDNUMBER		0x0000000E
#define ADMA_WHICHCHANNEL		0x0000000F
#define ADMA_SAMPLERESOLUTION	0x00000010
#define ADMA_DATAFORMAT			0x00000011

struct _HEADER0 {
	unsigned int 	SerialNumber:18;
	unsigned int 	SystemNumber:4;
	unsigned int 	WhichChannel:1;
	unsigned int 	BoardNumber:4;
	unsigned int 	SampleResolution:3;
	unsigned int 	DataFormat:2;
};

struct _HEADER1 {
	unsigned int 	RecordNumber:24;
	unsigned int 	BoardType:8;
};

struct _HEADER2 {
	U32	TimeStampLowPart;
};

struct _HEADER3 {
	unsigned int 	TimeStampHighPart:8;
	unsigned int 	ClockSource:2;
	unsigned int 	ClockEdge:1;
	unsigned int 	SampleRate:7;
	unsigned int 	InputRange:5;
	unsigned int 	InputCoupling:2;
	unsigned int 	InputImpedence:2;
	unsigned int 	ExternalTriggered:1;
	unsigned int 	ChannelBTriggered:1;
	unsigned int 	ChannelATriggered:1;
	unsigned int 	TimeOutOccurred:1;
	unsigned int 	ThisChannelTriggered:1;
};

typedef struct _ALAZAR_HEADER {
	struct _HEADER0 hdr0;
	struct _HEADER1 hdr1;
	struct _HEADER2 hdr2;
	struct _HEADER3 hdr3;
} ALAZAR_HEADER, *PALAZAR_HEADER;


typedef enum _AUTODMA_STATUS
{
    ADMA_Completed = 0,
    ADMA_Buffer1Invalid,
    ADMA_Buffer2Invalid,
    ADMA_BoardHandleInvalid,
    ADMA_InternalBuffer1Invalid,
    ADMA_InternalBuffer2Invalid,
    ADMA_OverFlow,
    ADMA_InvalidChannel,
    ADMA_DMAInProgress,
    ADMA_UseHeaderNotSet,
    ADMA_HeaderNotValid,
    ADMA_InvalidRecsPerBuffer,
	ADMA_InvalidTransferOffset,
	ADMA_InvalidCFlags
} AUTODMA_STATUS;
#define	ADMA_Success ADMA_Completed

// ****************************************************************************************
// ALAZAR CUSTOMER SUPPORT API
//
// Global API Functions
typedef enum {
	KINDEPENDENT = 0,
	KSLAVE = 1,
	KMASTER = 2,
	KLASTSLAVE = 3
} MSILS;
/******************************************
* Trouble Shooting Alazar Functions
******************************************/

RETURN_CODE AlazarReadWriteTest( HANDLE h,U32 *Buffer,U32 SizeToWrite,U32 SizeToRead);
RETURN_CODE AlazarMemoryTest( HANDLE h, U32 *errors );
RETURN_CODE AlazarBusyFlag( HANDLE h,int *BusyFlag);
RETURN_CODE AlazarTriggeredFlag( HANDLE h,int *TriggeredFlag);
U32	      AlazarBoardsFound();
HANDLE      AlazarOpen( char * BoardNameID); //e.x. ATS850-0, ATS850-1 ....
void        AlazarClose( HANDLE h);
MSILS       AlazarGetBoardKind( HANDLE h);
RETURN_CODE AlazarGetCPLDVersion( HANDLE h,U8 *Major,U8 *Minor);
RETURN_CODE AlazarGetChannelInfo( HANDLE h, U32 *MemSize, U8 *SampleSize);
RETURN_CODE AlazarGetSDKVersion(U8 *Major,U8 *Minor,U8 *Revision);
RETURN_CODE AlazarGetDriverVersion(U8 *Major,U8 *Minor,U8 *Revision);

// ****************************************************************************************
// Input Control API Functions
RETURN_CODE  AlazarInputControl( HANDLE h, U8 Channel, U32 Coupling, U32 InputRange, U32 Impedance);
RETURN_CODE  AlazarSetPosition( HANDLE h, U8 Channel, int PMPercent, U32 InputRange);
RETURN_CODE  AlazarSetExternalTrigger( HANDLE h, U32 Coupling, U32 Range);

// ****************************************************************************************
// Trigger API Functions
RETURN_CODE  AlazarSetTriggerDelay( HANDLE h, U32 Delay);
RETURN_CODE  AlazarSetTriggerTimeOut( HANDLE h, U32 to_ns);
U32          AlazarTriggerTimedOut( HANDLE h);
RETURN_CODE  AlazarGetTriggerAddress( HANDLE h, U32 Record, U32 *TriggerAddress, U32 *TimeStampHighPart, U32 *TimeStampLowPart);
RETURN_CODE  AlazarSetTriggerOperation( HANDLE h, U32 TriggerOperation
											  ,U32 TriggerEngine1/*j,K*/, U32 Source1, U32 Slope1, U32 Level1
											  ,U32 TriggerEngine2/*j,K*/, U32 Source2, U32 Slope2, U32 Level2);
RETURN_CODE	 AlazarGetTriggerTimestamp(HANDLE h, U32 Record, U64* Timestamp_samples);

// ****************************************************************************************
// Capture API Functions
RETURN_CODE  AlazarAbortCapture( HANDLE h);
RETURN_CODE  AlazarForceTrigger( HANDLE h);
RETURN_CODE	 AlazarForceTriggerEnable( HANDLE h);
RETURN_CODE  AlazarStartCapture( HANDLE h);
RETURN_CODE  AlazarCaptureMode( HANDLE h, U32 Mode);

// ****************************************************************************************
// OEM API Functions
RETURN_CODE AlazarStreamCapture( 
								HANDLE		h,
								void 		*Buffer,
								U32			BufferSize,
								U32			DeviceOption,
								U32			ChannelSelect,
								U32			*error
								);

RETURN_CODE AlazarHyperDisp(
							HANDLE		h,
							void 		*Buffer,
							U32			BufferSize,
							U8			*ViewBuffer,
							U32			ViewBufferSize,
							U32			NumOfPixels,
							U32			Option,
							U32			ChannelSelect,
							U32			Record,
							long		TransferOffset,
							U32			*error
							);

RETURN_CODE AlazarFastPRRCapture(
							HANDLE		h,
							void 		*Buffer,
							U32			BufferSize,
							U32			DeviceOption,
							U32			ChannelSelect,
							U32			*error
							);

// ****************************************************************************************
// Status API Functions
U32	AlazarBusy( HANDLE h);
U32	AlazarTriggered( HANDLE h);
U32	AlazarGetStatus( HANDLE h);

// ****************************************************************************************
// MulRec API Functions
U32         AlazarDetectMultipleRecord( HANDLE h);
RETURN_CODE AlazarSetRecordCount( HANDLE h, U32 Count);
RETURN_CODE AlazarSetRecordSize( HANDLE h, U32 PreSize, U32 PostSize);

// ****************************************************************************************
// Clock Control API Functions
RETURN_CODE AlazarSetCaptureClock( HANDLE h, U32 Source, U32 Rate, U32 Edge, U32 Decimation);
RETURN_CODE AlazarSetExternalClockLevel( HANDLE h, float percent);

// ****************************************************************************************
// Data Transfer API Functions
U32	AlazarRead( HANDLE h, U32 Channel, void *Buffer, int ElementSize, long Record, long TransferOffset, U32 TransferLength);

// ****************************************************************************************
// Individual Parameter API Functions
RETURN_CODE AlazarSetParameter( HANDLE h,U8 Channel,U32 Parameter,long Value);
RETURN_CODE AlazarSetParameterUL( HANDLE h,U8 Channel,U32 Parameter,U32 Value);
RETURN_CODE AlazarGetParameter( HANDLE h,U8 Channel,U32 Parameter,long *RetValue);
RETURN_CODE AlazarGetParameterUL( HANDLE h,U8 Channel,U32 Parameter,U32 *RetValue);

// ****************************************************************************************
// Handle and System Management API Functions
HANDLE AlazarGetSystemHandle(U32 sid);
U32 AlazarNumOfSystems(void);
U32 AlazarBoardsInSystemBySystemID(U32 sid);
U32 AlazarBoardsInSystemByHandle(HANDLE systemHandle);
HANDLE AlazarGetBoardBySystemID(U32 sid, U32 brdNum);
HANDLE AlazarGetBoardBySystemHandle(HANDLE systemHandle, U32 brdNum);
RETURN_CODE AlazarSetLED( HANDLE h, U32 state);

// ****************************************************************************************
// Board capability query functions
RETURN_CODE AlazarQueryCapability(HANDLE h, U32 request, U32 value, U32 *retValue);
U32 AlazarMaxSglTransfer(ALAZAR_BOARDTYPES bt);
RETURN_CODE AlazarGetMaxRecordsCapable(HANDLE h, U32 RecordLength, U32 *num);

// ****************************************************************************************
// Trigger Inquiry Functions
// Return values:
//              NEITHER   = 0
//              Channel A = 1
//              Channel B = 2
//              External  = 3
//              A AND B   = 4
//              A AND Ext = 5
//              B And Ext = 6
//              Timeout   = 7
U32 AlazarGetWhoTriggeredBySystemHandle( HANDLE systemHandle, U32 brdNum, U32 recNum);
U32 AlazarGetWhoTriggeredBySystemID( U32 sid, U32 brdNum, U32 recNum);

RETURN_CODE AlazarSetBWLimit( HANDLE h, U32 Channel, U32 enable);
RETURN_CODE AlazarSleepDevice( HANDLE h, U32 state);

// AUTODMA Related Routines
//
// Control Flags for AutoDMA used in AlazarStartAutoDMA
#define ADMA_EXTERNAL_STARTCAPTURE	0x00000001
#define ADMA_ENABLE_RECORD_HEADERS	0x00000008
#define ADMA_SINGLE_DMA_CHANNEL		0x00000010
#define ADMA_ALLOC_BUFFERS			0x00000020
#define ADMA_TRADITIONAL_MODE		0x00000000
#define ADMA_CONTINUOUS_MODE		0x00000100
#define ADMA_NPT					0x00000200
#define ADMA_TRIGGERED_STREAMING	0x00000400
#define ADMA_FIFO_ONLY_STREAMING    0x00000800 //ATS9462 mode
#define ADMA_INTERLEAVE_SAMPLES	    0x00001000
#define ADMA_GET_PROCESSED_DATA		0x00002000
#define ADMA_STREAM_TO_DISK			0x00004000

RETURN_CODE  AlazarStartAutoDMA(HANDLE h, void* Buffer1, U32 UseHeader, U32 ChannelSelect, long TransferOffset, U32 TransferLength, long RecordsPerBuffer, long RecordCount, AUTODMA_STATUS* error, U32 r1, U32 r2, U32 *r3, U32 *r4);
RETURN_CODE  AlazarGetNextAutoDMABuffer( HANDLE h, void* Buffer1, void* Buffer2, long* WhichOne, long* RecordsTransfered, AUTODMA_STATUS* error, U32 r1, U32 r2, long *TriggersOccurred, U32 *r4);
RETURN_CODE  AlazarGetNextBuffer( HANDLE h, void* Buffer1, void* Buffer2, long* WhichOne, long* RecordsTransfered, AUTODMA_STATUS* error, U32 r1, U32 r2, long *TriggersOccurred, U32 *r4);
RETURN_CODE  AlazarCloseAUTODma(HANDLE h);
RETURN_CODE  AlazarAbortAutoDMA(HANDLE h, void* Buffer, AUTODMA_STATUS* error, U32 r1, U32 r2, U32 *r3, U32 *r4);
U32  AlazarGetAutoDMAHeaderValue(HANDLE h, U32 Channel, void* DataBuffer, U32 Record, U32 Parameter, AUTODMA_STATUS *error);
float  AlazarGetAutoDMAHeaderTimeStamp(HANDLE h, U32 Channel, void* DataBuffer, U32 Record, AUTODMA_STATUS *error);
void  *AlazarGetAutoDMAPtr(HANDLE h, U32 DataOrHeader, U32 Channel, void* DataBuffer, U32 Record, AUTODMA_STATUS *error);
U32  AlazarWaitForBufferReady(HANDLE h, long tms);
RETURN_CODE  AlazarEvents(HANDLE h, U32 enable);

RETURN_CODE 
AlazarBeforeAsyncRead (
	HANDLE	hBoard, 
	U32		uChannelSelect, 
	long	lTransferOffset, 
	U32		uSamplesPerRecord, 
	U32		uRecordsPerBuffer, 
	U32		uRecordsPerAcquisition, 
	U32		uFlags
	);

#include "windows.h"
RETURN_CODE 
AlazarAsyncRead ( 
	HANDLE	    hBoard, 
	void       *pBuffer, 
	U32		    BytesToRead,
	OVERLAPPED *pOverlapped
	);

RETURN_CODE 
AlazarAbortAsyncRead (
	HANDLE	 hBoard
	);

RETURN_CODE 
AlazarPostAsyncBuffer (
	HANDLE  hDevice,
	void   *pBuffer, 
	U32     uBufferLength_bytes
	);

RETURN_CODE 
AlazarWaitAsyncBufferComplete (
	HANDLE  hDevice,
	void   *pBuffer, 
	U32     uTimeout_ms
	);


RETURN_CODE
AlazarWaitNextAsyncBufferComplete (
	HANDLE  hDevice,
	void   *pBuffer, 
	U32     uBufferLength_bytes,
	U32     uTimeout_ms
	);

RETURN_CODE
AlazarCreateStreamFileA (
	HANDLE hDevice, 
	const char *pszFilePath
	);

RETURN_CODE
AlazarCreateStreamFileW (
	HANDLE hDevice, 
	const WCHAR *pszFilePath
	);

#ifdef UNICODE 
#define AlazarCreateStreamFile AlazarCreateStreamFileW
#else
#define AlazarCreateStreamFile AlazarCreateStreamFileA
#endif

long AlazarFlushAutoDMA(HANDLE h);
void AlazarStopAutoDMA(HANDLE h);

// TimeStamp Control Api
RETURN_CODE AlazarResetTimeStamp(HANDLE h, U32 resetFlag);

RETURN_CODE AlazarReadRegister(HANDLE hDevice,U32 offset,U32 *retVal, U32 pswrd);
RETURN_CODE AlazarWriteRegister(HANDLE hDevice,U32 offset,U32 Val, U32 pswrd);

//
// DAC CONTROL API
RETURN_CODE AlazarDACSetting
(HANDLE h, U32 SetGet, U32 OriginalOrModified, U8 Channel, U32 DACNAME, U32 Coupling, U32 InputRange, U32 Impedance, U32 *getVal, U32 setVal, U32 *error);

RETURN_CODE
AlazarConfigureAuxIO (
	HANDLE		hDevice,
	U32			uMode,
	U32			uParameter
	);

// Convert RETURN_CODE to text
const char * 
AlazarErrorToText(
	RETURN_CODE code
	); 

#ifdef __cplusplus
}
#endif

#endif //_ALAZARAPI_H
