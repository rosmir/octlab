#ifndef __ALAZARERROR_H
#define __ALAZARERROR_H

/******************************************************************************
 *
 * File Name:
 *
 *      AlazarError.h
 *
 * Description:
 *
 *      This file defines all the error codes for Alazar SDK.
 *
 * Revision:
 *
 *      09-30-2003 : Alazar SDK v1.0
 *
 ******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

/******************************************
*             Definitions
******************************************/
#define API_RETURN_CODE_STARTS              0x200   /* Starting return code */


/* API Return Code Values */
typedef enum _RETURN_CODE
{
    ApiSuccess = API_RETURN_CODE_STARTS,	// 512
    ApiFailed,								// 513
    ApiAccessDenied,						// 514
    ApiDmaChannelUnavailable,				// 515
    ApiDmaChannelInvalid,					// 516
    ApiDmaChannelTypeError,					// 517
    ApiDmaInProgress,						// 518
    ApiDmaDone,								// 519
    ApiDmaPaused,							// 520
    ApiDmaNotPaused,						// 521
    ApiDmaCommandInvalid,					// 522
    ApiDmaManReady,							// 523
    ApiDmaManNotReady,						// 524
    ApiDmaInvalidChannelPriority,			// 525
    ApiDmaManCorrupted,						// 526
    ApiDmaInvalidElementIndex,				// 527
    ApiDmaNoMoreElements,					// 528
    ApiDmaSglInvalid,						// 529
    ApiDmaSglQueueFull,						// 530
    ApiNullParam,							// 531
    ApiInvalidBusIndex,						// 532
    ApiUnsupportedFunction,					// 533
    ApiInvalidPciSpace,						// 534
    ApiInvalidIopSpace,						// 535
    ApiInvalidSize,							// 536
    ApiInvalidAddress,						// 537
    ApiInvalidAccessType,					// 538
    ApiInvalidIndex,						// 539
    ApiMuNotReady,							// 540
    ApiMuFifoEmpty,							// 541
    ApiMuFifoFull,							// 542
    ApiInvalidRegister,						// 543
    ApiDoorbellClearFailed,					// 544
    ApiInvalidUserPin,						// 545
    ApiInvalidUserState,					// 546
    ApiEepromNotPresent,					// 547
    ApiEepromTypeNotSupported,				// 548
    ApiEepromBlank,							// 549
    ApiConfigAccessFailed,					// 550
    ApiInvalidDeviceInfo,					// 551
    ApiNoActiveDriver,						// 552
    ApiInsufficientResources,				// 553
    ApiObjectAlreadyAllocated,				// 554
    ApiAlreadyInitialized,					// 555
    ApiNotInitialized,						// 556
    ApiBadConfigRegEndianMode,				// 557
    ApiInvalidPowerState,					// 558
    ApiPowerDown,							// 559
    ApiFlybyNotSupported,					// 560
    ApiNotSupportThisChannel,				// 561
    ApiNoAction,							// 562
    ApiHSNotSupported,						// 563
    ApiVPDNotSupported,						// 564
    ApiVpdNotEnabled,						// 565
    ApiNoMoreCap,							// 566
    ApiInvalidOffset,						// 567
    ApiBadPinDirection,						// 568
    ApiPciTimeout,							// 569
    ApiDmaChannelClosed,					// 570
    ApiDmaChannelError,						// 571
    ApiInvalidHandle,						// 572
    ApiBufferNotReady,						// 573
    ApiInvalidData,							// 574
    ApiDoNothing,							// 575
    ApiDmaSglBuildFailed,					// 576
    ApiPMNotSupported,						// 577
    ApiInvalidDriverVersion,				// 578
    ApiWaitTimeout,							// 579
    ApiWaitCanceled,						// 580
	ApiBufferTooSmall,						// 581
	ApiBufferOverflow,						// 582
	ApiInvalidBuffer,						// 583
	ApiInvalidRecordsPerBuffer,				// 584
	ApiDmaPending,							// 585
	ApiLockAndProbePagesFailed,				// 586
	ApiWaitAbandoned,						// 587
	ApiWaitFailed,							// 588
	ApiTransferComplete,					// 589
	ApiPllNotLocked,						// 590
    ApiNotSupportedInDualChannelMode,       // 591
    ApiLastError							// Do not add API errors below this line
} RETURN_CODE;



#ifdef __cplusplus
}
#endif

#endif //__ALAZARERROR_H
